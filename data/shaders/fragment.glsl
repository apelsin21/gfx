#version 330 core

in vec2 f_uv;

uniform sampler2D sampler;

out vec4 out_color;

void main() {
    vec4 temp = texture(sampler, f_uv);

	gl_FragColor = vec4(1.0f, 1.0f, 1.0f, temp.r);
}
