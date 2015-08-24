#version 330 core

in vec3 f_pos;
in vec2 f_uv;

uniform sampler2D sampler;

out vec4 out_color;

void main() {
	gl_FragColor = texture(sampler, f_pos.xy);
}
