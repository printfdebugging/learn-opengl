#ifndef WINDOW_H
#define WINDOW_H

#include "GLFW/glfw3.h"
#include "glad/glad.h"

/*
DESCRIPTION:
    1. initialize glfw and set window hints
    2. create window, check for errors
    3. initialize glad, check for errors
    4. set frame buffer resize callback and return window

ERROR:
    returns NULL

MEMORY:
    the caller is responsible for freeing the GLFWwindow
    returned. window_destroy does that, so should be placed
    somewhere at the end of the program.
*/
GLFWwindow* window_create(GLuint width, GLuint height, const GLchar* title);

/*
DESCRIPTION:
    1. poll glfw events
    2. custom event handling code
*/
void window_process_input(GLFWwindow* window);

/*
DESCRIPTION:
    1. call destroy on GLFWwinodw
*/
void window_destroy(GLFWwindow* window);

/*
DESCRIPTION:
    1. make the backbuffer visible
*/
void window_refresh(GLFWwindow* window);

#endif
