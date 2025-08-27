#include <stdlib.h>
#include "shader.h"
#include "window.h"
#include "mesh.h"

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

    glVertexAttribPointer(MESH_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(MESH_ATTRIBUTE_POSITION);

    // Reset for safety.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    struct shader_program program = shader_program_create("shaders/shader.vert", "shaders/shader.frag");
    if (!program.shader_program) {
        return EXIT_FAILURE;
    }

    // This could change later but for the time being, we always use the same color, the same shader and the same model.
    // Pulled outside of the main loop.
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glUseProgram(program.shader_program);
    glBindVertexArray(VAO);

    while (!glfwWindowShouldClose(window)) {
        // (1) Event phase.
        window_process_input(window);

        // (2) Render phase.
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // (3) Swap phase.
        window_refresh(window);
    }

    // Cleanup.
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    shader_program_destroy(program);
    window_destroy(window);

    return EXIT_SUCCESS;
}
