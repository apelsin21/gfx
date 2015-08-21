#version 130

in vec3 v_pos;
in vec2 v_uv;

uniform mat4 v_projection;

out vec2 f_uv;

void main() {
	f_uv = v_uv;
    gl_Position = v_projection * vec4(v_pos.xyz, 1.0);
}
