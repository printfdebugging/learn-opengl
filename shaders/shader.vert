#version 330 core

in vec3 vertex_position;
in vec3 color;
out vec4 vertex_color;

uniform float offset_x;

void main() {
    gl_Position = vec4(
        clamp(vertex_position.x + offset_x, -1, 1),
        vertex_position.y,
        vertex_position.z, 1.0
    );
    vertex_color = vec4(color, 1.0);
}