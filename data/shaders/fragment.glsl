#version 330 core

in vec2 f_uv;

uniform sampler2D sampler;

out vec4 out_color;

void main() {

    vec4 temp = texture(sampler, f_uv);

	if(temp.r < 0.3)
		discard;

	gl_FragColor = temp;
}
