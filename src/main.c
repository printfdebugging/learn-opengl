#include <stdio.h>
#include <stdlib.h>
#include "shader.h"
#include "window.h"
#include "logger.h"

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

static void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main() {
    GLFWwindow *window = window_create(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    if (!window) {
        return EXIT_FAILURE;
    }

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);

    // Reset for safety.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLuint vertex_shader = shader_load_from_file("shaders/shader.vert", GL_VERTEX_SHADER);
    if (!vertex_shader) {
        return EXIT_FAILURE;
    }

    GLuint fragment_shader = shader_load_from_file("shaders/shader.frag", GL_FRAGMENT_SHADER);
    if (!fragment_shader) {
        return EXIT_FAILURE;
    }

    GLuint shader_program;
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    int success = 0;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        char inf_log[512];
        glGetProgramInfoLog(shader_program, 512, NULL, inf_log);  // FIXME: Obtain the length of the log dynamically.
        ERROR("failed to link shader program: %s\n", inf_log);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // This could change later but for the time being, we always use the same color, the same shader and the same model.
    // Pulled outside of the main loop.
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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
    window_destroy(window);

    return EXIT_SUCCESS;
}
