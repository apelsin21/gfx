#version 330 core

in vec3 v_pos;
in vec2 v_uv;

uniform mat4 v_projection;

out vec2 f_uv;
out vec3 f_pos;
out float f_id;

void main() {
	f_uv = v_uv;
	f_pos = v_pos;
	f_id = gl_VertexID;
    gl_Position = v_projection * vec4(v_pos.xyz, 1.0);
}
