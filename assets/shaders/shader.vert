#version 330 core

/*
    the input variables are predefined in the program
    and they start with an '_' at the front.
*/
in  vec3 _position;
in  vec3 _color;
in  vec2 _uv;

/* 
    note that these should match with the 'in'
    variables in the fragment shader.

    variables which are created and consumed 
    within the graphics pipeline don't have an '_'
    in front of them.
*/
out vec4 color;
out vec2 uv;


void main() {
    gl_Position = vec4(_position.x, _position.y, _position.z, 1.0);
    color       = vec4(_color.xyz, 1.0);
    uv          = _uv;
}