#include "mesh.h"
#include "logger.h"
#include "shader.h"
#include <unistd.h>

struct mesh mesh_create() {
    struct mesh mesh = {
        .vertex_array = 0,
        .vertices_buffer = 0,
        .indices_buffer = 0,
        .shader_program = {0},
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    mesh.vertex_array = vao;

    return mesh;
}

void mesh_bind(struct mesh *mesh) {
    glBindVertexArray(mesh->vertex_array);
    glUseProgram(mesh->shader_program.shader_program);
}

void mesh_unbind() {
    glBindVertexArray(0);
    glUseProgram(0);
}

/*
DESCRIPTION:
    1. creates a vbo
    2. binds it to GL_ARRAY_BUFFER
    3. loads vertices into it as GL_STATIC_DRAW
    4. sets GL_ARRAY_BUFFER data at index MESH_ATTRIBUTE_POSITION in vao
    5. enables data at index MESH_ATTRIBUTE_POSITION in vao
    6. unbinds vbo from GL_ARRAY_BUFFER
*/
static void __mesh_bind_vertex_data(struct mesh *mesh, const GLfloat *vertices, GLuint count, GLuint stride, GLenum draw_type) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, count, vertices, draw_type);

    glVertexAttribPointer(MESH_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, stride, NULL);
    glEnableVertexAttribArray(MESH_ATTRIBUTE_POSITION);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    mesh->vertex_array = vbo;
}

void mesh_load_vertices(struct mesh *mesh, const GLfloat *vertices, GLuint count, GLuint stride, GLenum draw_type) {
    mesh_bind(mesh);
    __mesh_bind_vertex_data(mesh, vertices, count, stride, draw_type);
    mesh_unbind();
}

void mesh_load_shader_program(struct mesh *mesh, const char *vertex_shader_source, const char *fragment_shader_source) {
    struct shader_program program = shader_program_create(vertex_shader_source, fragment_shader_source);
    mesh->shader_program = program;
}

void mesh_destroy(struct mesh mesh) {
    glDeleteBuffers(1, &mesh.vertices_buffer);
    glDeleteBuffers(1, &mesh.indices_buffer);
    glDeleteVertexArrays(1, &mesh.vertex_array);
    shader_program_destroy(mesh.shader_program);
}
