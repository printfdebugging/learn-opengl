#version 330 core

out vec4 fragment_color;
in vec4 pos_to_frag_shader;

void main() {
    fragment_color = pos_to_frag_shader;
}
