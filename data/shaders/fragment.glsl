#version 330 core

in vec2 f_uv;

uniform sampler2D sampler;

out vec4 out_color;

void main() {
    out_color = texture(sampler, f_uv);
}
