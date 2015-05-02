#version 330 core

in vec3 v_pos;
in vec2 v_uv;

out vec2 f_uv;

void main() {
    f_uv = v_uv;

	vec2 corner;
	switch(gl_VertexID) {
		case 0:
			corner = vec2(v_pos.x-(1*v_pos.z), v_pos.y-(1*v_pos.z)); //bl
		break;

		case 1:
			corner = vec2(v_pos.x+(1*v_pos.z), v_pos.y-(1*v_pos.z)); //br
		break;

		case 2:
			corner = vec2(v_pos.x-(1*v_pos.z), v_pos.y+(1*v_pos.z)); //tl
		break;

		case 3:
			corner = vec2(v_pos.x+(1*v_pos.z), v_pos.y-(1*v_pos.z)); //br
		break;

		case 4:
			corner = vec2(v_pos.x+(1*v_pos.z), v_pos.y+(1*v_pos.z)); //tr
		break;

		case 5:
			corner = vec2(v_pos.x-(1*v_pos.z), v_pos.y+(1*v_pos.z)); //tl
		break;
		case 6:
			corner = vec2(v_pos.x-(1*v_pos.z), v_pos.y-(1*v_pos.z)); //bl
		break;
	}
	
    gl_Position = vec4(corner.xy, 0.0, 1.0);
}
