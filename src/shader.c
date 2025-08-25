#define _GNU_SOURCE
#include "shader.h"

#include <stdio.h>
#include <stdlib.h>

const char *read_shader_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "failed to read shader file: %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (length < 0) {
        fclose(file);
        fprintf(stderr, "failed to get the shader file's length: %s\n", filename);
        return NULL;
    }

    char *buffer = malloc(length + 1);
    if (!buffer) {
        fclose(file);
        fprintf(stderr, "failed to allocate memory for shader file: %s\n", filename);
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    fclose(file);

    return buffer;
}
