#include <stdio.h>
#include <stdlib.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "shader.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const char *WINDOW_TITLE = "LearnOpenGL";

GLfloat vertices[] = {
    -0.5f,
    -0.5f,
    0.0f,
    0.5f,
    -0.5f,
    0.0f,
    0.0f,
    0.5f,
    0.0f,
};

static void framebuffer_resize_callback(GLFWwindow *window, int width, int height) {
    (void) window;
    glViewport(0, 0, width, height);
}

static void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "failed to initialize glfw\n");
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For MacOS.

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (!window) {
        fprintf(stderr, "failed to create glfw winodw\n");
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGL()) {
        fprintf(stderr, "failed to initialize glad\n");
        return EXIT_FAILURE;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float), NULL);
    glEnableVertexAttribArray(0);

    // Reset for safety.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    const char *vertex_shader_source = read_shader_file("shaders/shader.vert");
    if (!vertex_shader_source) {
        fprintf(stderr, "failed to load vertex shader source\n");
        return EXIT_FAILURE;
    }

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    int success;
    char info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log); // FIXME: Obtain the length of the log dynamically.
        fprintf(stderr, "failed to comile vertex shader: %s\n", info_log);
    }

    const char *fragment_shader_source = read_shader_file("shaders/shader.frag");
    if (!fragment_shader_source) {
        fprintf(stderr, "failed to load fragment shader source\n");
        return EXIT_FAILURE;
    }

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    success = 0;
    char info_log2[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log2); // FIXME: Obtain the length of the log dynamically.
        fprintf(stderr, "failed to comile fragment shader: %s\n", info_log2);
    }

    GLuint shader_program;
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    success = 0;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        char inf_log[512];
        glGetProgramInfoLog(shader_program, 512, NULL, inf_log); // FIXME: Obtain the length of the log dynamically.
        fprintf(stderr, "failed to link shader program: %s\n", inf_log);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // This could change later but for the time being, we always use the same color, the same shader and the same model.
    // Pulled outside of the main loop.
    glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
    glUseProgram(shader_program);
    glBindVertexArray(VAO);

    while (!glfwWindowShouldClose(window)) {
        // (1) Event phase.
        glfwPollEvents();
        process_input(window);

        // (2) Render phase.
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // (3) Swap phase.
        glfwSwapBuffers(window);
    }

    // Cleanup.
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(shader_program);

    glfwTerminate();

    return EXIT_SUCCESS;
}
