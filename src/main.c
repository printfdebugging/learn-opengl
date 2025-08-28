#include <stdlib.h>
#include "shader.h"
#include "window.h"
#include "mesh.h"
#include "renderer.h"

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

    struct mesh mesh = mesh_create();
    mesh_load_vertices(&mesh, vertices, sizeof(vertices), 3 * sizeof(float), GL_STATIC_DRAW);
    mesh_load_shader_program(&mesh, "shaders/shader.vert", "shaders/shader.frag");

    renderer_init();

    while (!glfwWindowShouldClose(window)) {
        window_process_input(window);

        renderer_prepare();
        renderer_render(mesh);

        window_refresh(window);
    }

    mesh_destroy(mesh);
    window_destroy(window);

    return EXIT_SUCCESS;
}
