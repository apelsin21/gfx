#version 130

in vec2 f_uv;

uniform sampler2D sampler;

void main() {
	gl_FragColor = texture2D(sampler, f_uv);
}
