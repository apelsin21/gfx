#version 330 core

in vec2 v_pos;
in vec2 v_uv;

out vec2 f_uv;

void main() {
	f_uv = v_uv;
	gl_Position = vec4(v_pos.xy, 0.0, 1.0);
}
