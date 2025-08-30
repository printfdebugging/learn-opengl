#include "mesh.h"
#include "logger.h"
#include <unistd.h>

struct mesh mesh_create() {
    struct mesh mesh = {
        .vertex_array = 0,
        .vertices_buffer = 0,
        .vertices_count = 0,
        .indices_buffer = 0,
        .indices_count = 0,
        .shader_program = {0},
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    mesh.vertex_array = vao;

    return mesh;
}

GLboolean mesh_bind_vertex_array(struct mesh *mesh) {
    if (!mesh->vertex_array) {
        ERROR("attempt to bind invalid mesh->vertex_array=%i\n", mesh->vertex_array);
        return GL_FALSE;
    }
    glBindVertexArray(mesh->vertex_array);
    return GL_TRUE;
}

GLboolean mesh_bind_shader_program(struct mesh *mesh) {
    if (!mesh->vertex_array || !mesh->shader_program.shader_program) {
        ERROR("attempt to bind invalid mesh->shader_program.program=%i\n", mesh->shader_program.shader_program);
        return GL_FALSE;
    }
    glUseProgram(mesh->shader_program.shader_program);
    return GL_TRUE;
}

GLboolean mesh_bind(struct mesh *mesh) {
    if (!mesh_bind_vertex_array(mesh) || !mesh_bind_shader_program(mesh)) {
        return GL_FALSE;
    }
    return GL_TRUE;
}

void mesh_unbind() {
    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
    mesh->vertices_count = count;
}

static void __mesh_bind_index_data(struct mesh *mesh, const GLuint *indices, GLuint count, GLenum draw_type) {
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indices, draw_type);
    mesh->indices_buffer = ebo;
    mesh->indices_count = count;
}

GLboolean mesh_load_vertices(struct mesh *mesh, const GLfloat *vertices, GLuint count, GLuint stride, GLenum draw_type) {
    if (!mesh_bind_vertex_array(mesh)) {
        return GL_FALSE;
    }
    __mesh_bind_vertex_data(mesh, vertices, count, stride, draw_type);
    mesh_unbind();
    return GL_TRUE;
}

GLboolean mesh_load_indices(struct mesh *mesh, const GLuint *indices, GLuint count, GLenum draw_type) {
    if (!mesh_bind_vertex_array(mesh)) {
        return GL_FALSE;
    }
    __mesh_bind_index_data(mesh, indices, count, draw_type);
    mesh_unbind();
    return GL_TRUE;
}

GLboolean mesh_load_shader_program(struct mesh *mesh, const char *vertex_shader_source, const char *fragment_shader_source) {
    struct shader_program program = shader_program_create(vertex_shader_source, fragment_shader_source);
    if (!program.shader_program) {
        return GL_FALSE;
    }
    mesh->shader_program = program;
    return GL_TRUE;
}

void mesh_destroy(struct mesh mesh) {
    glDeleteBuffers(1, &mesh.vertices_buffer);
    glDeleteBuffers(1, &mesh.indices_buffer);
    glDeleteVertexArrays(1, &mesh.vertex_array);
    shader_program_destroy(mesh.shader_program);
}
