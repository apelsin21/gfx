#version 130

in vec2 f_uv;

uniform sampler2D sampler;

out vec3 out_color;

void main() {
	out_color = texture2D(sampler, f_uv).xyz;
}
