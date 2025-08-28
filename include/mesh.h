#ifndef MESH_H
#define MESH_H

#include "glad/glad.h"
#include "shader.h"

enum mesh_attribute {
    MESH_ATTRIBUTE_POSITION = 0,
};

static const char* shader_var_names[] = {
    [MESH_ATTRIBUTE_POSITION] = "vertex_position",
};

struct mesh {
    GLuint vertex_array;
    GLuint vertices_buffer;
    GLuint indices_buffer;

    struct shader_program shader_program;
};

/*
DESCRIPTION:
    1. creates an empty mesh object
    2. creates a vao and binds it to the mesh
*/
struct mesh mesh_create();

/*
DESCRIPTION:
    1. makes the vao current
    2. uses the mesh's shader program
*/
void mesh_bind(struct mesh* mesh);

/*
DESCRIPTION:
    1. unbinds any vao by binding 0
    2. unbinds mesh's shader program by binding 0
*/
void mesh_unbind();

/*
DESCRIPTION:
    1. makes the vao current
    2. creates a vbo with vertices and binds it to vao
    3. unbinds the current vao
*/
void mesh_load_vertices(struct mesh *mesh, const GLfloat *vertices, GLuint count, GLuint stride, GLenum draw_type);

/*
DESCRIPTION:
    1. loads a shader program
    2. saves it in the mesh
*/
void mesh_load_shader_program(struct mesh* mesh, const char* vertex_shader_source, const char* fragment_shader_source);

/*
DESCRIPTION:
    1. destroys the vbos and the vao
    2. destroys the shader program
*/
void mesh_destroy(struct mesh mesh);

#endif
