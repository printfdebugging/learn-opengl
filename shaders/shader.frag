#version 330 core

out vec4 fragment_color;
in vec4 vertex_color;

uniform vec4 background_color;

void main() {
    fragment_color = background_color;
}
