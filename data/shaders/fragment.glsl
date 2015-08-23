#version 330 core

in vec3 f_pos;
in vec2 f_uv;

uniform sampler2D sampler;

out vec4 out_color;

float rand(vec2 co){
    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

void main() {
	gl_FragColor = texture(sampler, f_pos.xy) * vec4(f_pos.y+0.1, f_pos.y+0.1, f_pos.y+0.1, 1.0);
}
