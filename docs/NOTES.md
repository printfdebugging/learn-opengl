# notes

## vertex and fragment shaders
- first v runs for each vertex in the model
- then once each vertex has been processed, they have a value i.e the output of vertex shader.
- then fragment shader runs for each pixel and the values assigned to the vertices by the vertex shader are linearly interpolated.  remember the cat factor and the dog distance example
- the output of the vertex shader can be anything, any number/combination of floats, vectors and matrices
- the output of the fragment shader is fixed, the color the pixel.

## opengl specification
- https://registry.khronos.org/OpenGL/specs/gl/glspec33.core.pdf
- it's a must read once you get comfortable with opengl

## glfw and event polling
- we can register callbacks with glfw, like the framebuffer_resize_callback
- `glfwPollEvens()` listens for user events, updates window state and calls the registered callback functions

## rendering
- opengl  is a 3d graphics library and takes input `normalized device coordinates` i.e. in \[-1, 1\] range
- i wonder how many decimal places of precision is supported in this coordinate space and what are the implications of having high precision floats there
- ndc are transformed to screen-space coordinates via the viewport transform
