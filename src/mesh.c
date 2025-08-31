#include "mesh.h"
#include "logger.h"
#include <unistd.h>

struct mesh mesh_create() {
    struct mesh mesh = {
        .vao = 0,
        .vbo = 0,
        .vbo_size = 0,
        .ebo = 0,
        .ebo_size = 0,
        .shader_program = {0},
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    mesh.vao = vao;

    return mesh;
}

static GLboolean mesh_bind_vertex_array(struct mesh *mesh) {
    if (!mesh->vao) {
        ERROR("attempt to bind invalid mesh->vertex_array=%i\n", mesh->vao);
        return GL_FALSE;
    }
    glBindVertexArray(mesh->vao);
    return GL_TRUE;
}

static GLboolean mesh_bind_shader_program(struct mesh *mesh) {
    if (!mesh->vao || !mesh->shader_program.shader_program) {
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

GLboolean mesh_load_vertices(struct mesh *mesh, const GLfloat *vertices, GLuint size, GLuint stride, GLenum draw_type) {
    if (!mesh_bind_vertex_array(mesh)) {
        return GL_FALSE;
    }

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, draw_type);

    glVertexAttribPointer(MESH_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, stride, NULL);
    glEnableVertexAttribArray(MESH_ATTRIBUTE_POSITION);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    mesh->vbo = vbo;
    mesh->vbo_size = size;

    mesh_unbind();
    return GL_TRUE;
}

GLboolean mesh_load_indices(struct mesh *mesh, const GLuint *indices, GLuint size, GLenum draw_type) {
    if (!mesh_bind_vertex_array(mesh)) {
        return GL_FALSE;
    }

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, draw_type);
    mesh->ebo = ebo;
    mesh->ebo_size = size;

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
    glDeleteBuffers(1, &mesh.vbo);
    glDeleteBuffers(1, &mesh.ebo);
    glDeleteVertexArrays(1, &mesh.vao);
    shader_program_destroy(mesh.shader_program);
}
