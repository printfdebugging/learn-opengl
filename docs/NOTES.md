# notes

## vertex and fragment shaders
- first v runs for each vertex in the model
- then once each vertex has been processed, they have a value i.e the output of vertex shader.
- then fragment shader runs for each pixel and the values assigned to the vertices by the vertex shader are linearly interpolated.  remember the cat factor and the dog distance example
- the output of the vertex shader can be anything, any number/combination of floats, vectors and matrices
- the output of the fragment shader is fixed, the color the pixel.
