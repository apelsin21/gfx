#version 130

in vec4 v_pos;
in vec4 v_uv;

uniform mat4 projection;

out vec2 f_uv;

void main() {
	vec2 corner = v_pos.xy;

	if(gl_VertexID == 0) { //bottom left
		corner += vec2(-1*v_pos.z, -1*v_pos.w);
		f_uv = vec2(v_uv.xy);
	} else if(gl_VertexID == 1) {
		corner += vec2(1*v_pos.z, -1*v_pos.w);
		f_uv = vec2(v_uv.z, v_uv.y);
	} else if(gl_VertexID == 2) { //top left
		corner += vec2(-1*v_pos.z, 1*v_pos.w);
		f_uv = vec2(v_uv.x, v_uv.w);
	} else if(gl_VertexID == 3) {
		corner += vec2(1*v_pos.z, -1*v_pos.w);
		f_uv = vec2(v_uv.z, v_uv.y);
	} else if(gl_VertexID == 4) {
		corner += vec2(1*v_pos.z, 1*v_pos.w);
		f_uv = vec2(v_uv.z, v_uv.w);
	} else if(gl_VertexID == 5) {
		corner += vec2(-1*v_pos.z, 1*v_pos.w);
		f_uv = vec2(v_uv.x, v_uv.w);
	}
	
    gl_Position = projection * vec4(corner.xy, 0.0, 1.0);
}
