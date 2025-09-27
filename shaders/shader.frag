#version 330 core

out vec4 fragment_color;
in vec4 vertex_color;

void main() {
    fragment_color = vertex_color;
}
