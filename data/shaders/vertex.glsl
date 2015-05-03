#version 330 core

in vec3 v_pos;
in vec4 v_uv;

out vec2 f_uv;

void main() {
	vec2 corner = v_pos.xy;
	switch(gl_VertexID) {
		case 0: //bl
			corner += vec2(-1*v_pos.z, -1*v_pos.z);
			f_uv = vec2(v_uv.xy);
		break;

		case 1: //br
			corner += vec2(1*v_pos.z, -1*v_pos.z);
			f_uv = vec2(v_uv.z, v_uv.y);
		break;

		case 2: //tl
			corner += vec2(-1*v_pos.z, 1*v_pos.z);
			f_uv = vec2(v_uv.x, v_uv.w);
		break;

		case 3: //br
			corner += vec2(1*v_pos.z, -1*v_pos.z);
			f_uv = vec2(v_uv.z, v_uv.y);
		break;

		case 4: //tr
			corner += vec2(1*v_pos.z, 1*v_pos.z);
			f_uv = vec2(v_uv.z, v_uv.w);
		break;

		case 5: //tl
			corner += vec2(-1*v_pos.z, 1*v_pos.z);
			f_uv = vec2(v_uv.x, v_uv.w);
		break;
	}
	
    gl_Position = vec4(corner.xy, 0.0, 1.0);
}
