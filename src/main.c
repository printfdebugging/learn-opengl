#include <stdlib.h>
#include "shader.h"
#include "window.h"
#include "mesh.h"
#include "renderer.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const char *WINDOW_TITLE = "LearnOpenGL";

/* clang-format off */
GLfloat right_rect[] = {
    0.75f, 0.75f, 0.0f,
    0.75f, 0.25f, 0.0f,
    0.25f, 0.25f, 0.0f,
    0.25f, 0.75f, 0.0f,
};

GLfloat left_rect[] = {
    -0.25f, 0.75f, 0.0f,
    -0.75f, 0.75f, 0.0f,
    -0.75f, 0.25f, 0.0f,
    -0.25f, 0.25f, 0.0f,
};

GLuint right_rect_indices[] = {
    0, 1, 2,
    0, 2, 3,
};

GLuint left_rect_indices[] = {
    0, 1, 2,
    0, 2, 3,
};
/* clang-format on */

int main() {
    GLFWwindow *window = window_create(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    if (!window) {
        return EXIT_FAILURE;
    }

    struct mesh right_rect_mesh = mesh_create();
    if (!mesh_load_vertices(&right_rect_mesh, right_rect, sizeof(right_rect), 3 * sizeof(float), GL_STATIC_DRAW)) {
        return EXIT_FAILURE;
    }
    if (!mesh_load_indices(&right_rect_mesh, right_rect_indices, sizeof(right_rect_indices), GL_STATIC_DRAW)) {
        return EXIT_FAILURE;
    }
    if (!mesh_load_shader_program(&right_rect_mesh, "shaders/shader.vert", "shaders/shader.frag")) {
        return EXIT_FAILURE;
    }

    struct mesh left_rect_mesh = mesh_create();
    if (!mesh_load_vertices(&left_rect_mesh, left_rect, sizeof(left_rect), 3 * sizeof(float), GL_STATIC_DRAW)) {
        return EXIT_FAILURE;
    }
    if (!mesh_load_indices(&left_rect_mesh, left_rect_indices, sizeof(left_rect_indices), GL_STATIC_DRAW)) {
        return EXIT_FAILURE;
    }
    if (!mesh_load_shader_program(&left_rect_mesh, "shaders/shader.vert", "shaders/shader.frag")) {
        return EXIT_FAILURE;
    }

    renderer_init();

    while (!glfwWindowShouldClose(window)) {
        window_process_input(window);

        renderer_prepare();

        renderer_render(right_rect_mesh, INDICES_WIREFRAME);
        renderer_render(left_rect_mesh, INDICES_WIREFRAME);

        window_refresh(window);
    }

    mesh_destroy(right_rect_mesh);
    mesh_destroy(left_rect_mesh);
    window_destroy(window);

    return EXIT_SUCCESS;
}
