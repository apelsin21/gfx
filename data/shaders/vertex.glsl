#version 330 core

in vec4 v_pos;
in vec4 v_uv;

out vec2 f_uv;

void main() {
	vec2 corner = v_pos.xy;
	switch(gl_VertexID) {
		case 0: //bottom left
			corner += vec2(-1*v_pos.z, -1*v_pos.w);
			f_uv = vec2(v_uv.xy);
		break;

		case 1: //bottom right
			corner += vec2(1*v_pos.z, -1*v_pos.w);
			f_uv = vec2(v_uv.z, v_uv.y);
		break;

		case 2: //top left
			corner += vec2(-1*v_pos.z, 1*v_pos.w);
			f_uv = vec2(v_uv.x, v_uv.w);
		break;

		case 3: //bottom right 
			corner += vec2(1*v_pos.z, -1*v_pos.w);
			f_uv = vec2(v_uv.z, v_uv.y);
		break;

		case 4: //top right
			corner += vec2(1*v_pos.z, 1*v_pos.w);
			f_uv = vec2(v_uv.z, v_uv.w);
		break;

		case 5: //top left
			corner += vec2(-1*v_pos.z, 1*v_pos.w);
			f_uv = vec2(v_uv.x, v_uv.w);
		break;
	}
	
    gl_Position = vec4(corner.xy, 0.0, 1.0);
}
