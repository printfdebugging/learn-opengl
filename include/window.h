#ifndef WINDOW_H
#define WINDOW_H

#include "GLFW/glfw3.h"
#include "glad/glad.h"

GLFWwindow* window_create(GLuint width, GLuint height, const GLchar* title);
void window_process_input(GLFWwindow* window);
void window_destroy(GLFWwindow* window);

#endif