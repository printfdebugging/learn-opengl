#version 330 core

in vec3 vertex_position;
in vec3 color;
out vec4 pos_to_frag_shader;

void main() {
    gl_Position = vec4(
        vertex_position.x,
        vertex_position.y,
        vertex_position.z, 1.0
    );
    pos_to_frag_shader= gl_Position;
}