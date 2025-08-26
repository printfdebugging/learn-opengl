#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"

/*
    returns 0 on error
*/
GLuint shader_load_from_file(const char *filename, GLenum shader_type);

#endif
