#define _GNU_SOURCE
#include "shader.h"
#include "logger.h"

#include <stdio.h>
#include <stdlib.h>

/*
DESCRIPTION:
    1. open the file, check for errors
    2. get the file length using fseek, check for errors
    3. allocate length + 1 size memory, check for errors
    4. return a '\0' terminated string

ERRORS:
    returns NULL

MEMORY:
    the caller is responsible for freeing the dynamically
    allocated string.
*/
static const char *read_shader_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        ERROR("failed to read shader file: %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (length < 0) {
        fclose(file);
        ERROR("failed to get the shader file's length: %s\n", filename);
        return NULL;
    }

    char *buffer = malloc(length + 1);
    if (!buffer) {
        fclose(file);
        ERROR("failed to allocate memory for shader file: %s\n", filename);
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    fclose(file);

    return buffer;
}

GLuint shader_load_from_file(const char *filename, GLenum shader_type) {
    const char *shader_source = read_shader_file(filename);
    if (!shader_source) {
        return 0;
    }

    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_source, NULL);
    glCompileShader(shader);
    free((void *) shader_source);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetShaderInfoLog(shader, 512, NULL, info_log);  // FIXME: Obtain the length of the log dynamically.
        ERROR("failed to comile shader file (%s): %s\n", filename, info_log);
        return 0;
    }

    return shader;
}

struct shader_program shader_program_create(const char *vertex_shader_source, const char *fragment_shader_source) {
    struct shader_program program = {
        .shader_program = 0,
        .vertex_shader = 0,
        .fragment_shader = 0,
    };

    GLuint vertex_shader = shader_load_from_file(vertex_shader_source, GL_VERTEX_SHADER);
    if (!vertex_shader) {
        return program;
    }

    GLuint fragment_shader = shader_load_from_file(fragment_shader_source, GL_FRAGMENT_SHADER);
    if (!fragment_shader) {
        return program;
    }

    GLuint shader_program;
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    shader_program_bind_attribute(program, 0, "vertex_position");
    glLinkProgram(shader_program);

    int success = 0;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);  // FIXME: Obtain the length of the log dynamically.
        ERROR("failed to link shader program: %s\n", info_log);

        glDeleteShader(program.vertex_shader);
        glDeleteShader(program.fragment_shader);
        return program;
    }

    program.vertex_shader = vertex_shader;
    program.fragment_shader = fragment_shader;
    program.shader_program = shader_program;
    return program;
}

void shader_program_destroy(struct shader_program program) {
    glDeleteShader(program.vertex_shader);
    glDeleteShader(program.fragment_shader);
    glDeleteProgram(program.shader_program);
}

void shader_program_bind_attribute(struct shader_program program, GLuint attribute, const char *variable_name) {
    glBindAttribLocation(program.shader_program, attribute, variable_name);
}
