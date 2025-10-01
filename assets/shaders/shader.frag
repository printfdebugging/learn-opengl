#version 330 core

in  vec4 color;
in  vec2 uv;

/*
    variables which are not consumed by the shaders 
    but are passed on to opengl have an '_' at the
    end.
*/
out vec4 color_;


/*
    uniforms are all upper case. sampler2D are just integers
    under the hood, handles to shader objects. that's why we set
    them with glUniform1i in the c code.
*/
uniform sampler2D TEXTURE0;
uniform sampler2D TEXTURE1;


void main() {
    color_ = mix(
        texture(TEXTURE0, uv),
        texture(TEXTURE1, uv),
        0.2
    );
}
