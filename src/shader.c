#define _GNU_SOURCE
#include "shader.h"
#include "logger.h"

#include <stdio.h>
#include <stdlib.h>

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
        ERROR("failed to load vertex shader source\n");
        return 0;
    }

    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_source, NULL);
    glCompileShader(shader);

    int success;
    char info_log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, info_log);  // FIXME: Obtain the length of the log dynamically.
        ERROR("failed to comile shader file (%s): %s\n", filename, info_log);
        free((void *) shader_source);
        return 0;
    }

    free((void *) shader_source);
    return shader;
}
