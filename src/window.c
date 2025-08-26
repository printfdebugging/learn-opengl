#include <stdio.h>
#include "window.h"

static void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
    (void) window;
    glViewport(0, 0, width, height);
}

GLFWwindow* window_create(GLuint width, GLuint height, const GLchar* title) {
    if (!glfwInit()) {
        fprintf(stderr, "failed to initialize glfw\n");
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // For MacOS.
#endif

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        fprintf(stderr, "failed to create glfw winodw\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        fprintf(stderr, "failed to initialize glad\n");
        glfwTerminate();
        return NULL;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
    return window;
}

void window_destroy(GLFWwindow* window) {
    glfwDestroyWindow(window);
}