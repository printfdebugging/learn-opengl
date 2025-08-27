#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"

struct shader_program {
    GLuint shader_program;
    GLuint vertex_shader;
    GLuint fragment_shader;
};

/*
DESCRIPTION:
    1. create the vertex and fragment shader objects
    2. create a shader program and attach the shaders
    3. link the program and check for errors
    4. initialize struct shader_program and return it

ERROR:
    returns a zero initialized struct shader_program

MEMORY:
    the caller is responsible for freeing the shader and
    shader program objects created in this function.
    shader_program_destroy does just that.
*/
struct shader_program shader_program_create(const char* vertex_shader_source, const char* fragment_shader_source);

/*
DESCRIPTION:
    1. destroy the vertex and fragment shaders
    2. destroy the shader program
*/
void shader_program_destroy(struct shader_program program);

/*
DESCRIPTION:
    assigns a vertex attribute index (location) to a named
    attribute variable in a shader program, before you link
    the program.
*/
void shader_program_bind_attribute(struct shader_program program, GLuint attribute, const char* variable_name);

/*
DESCRIPTION:
    1. read shader file, check for errors
    2. create a shader object  and set it's source
    3. compile the shader and check for errors
    4. return handle to the shader object

ERROR:
    returns 0

MEMORY:
    the caller is responsible for freeing the shader object
    created in this function.
*/
GLuint shader_load_from_file(const char* filename, GLenum shader_type);

#endif
