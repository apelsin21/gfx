#version 130

in vec3 v_pos;
in vec3 v_normal;

uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 f_pos;
out vec3 f_normal;
out vec3 normal_cameraspace;
out vec3 light_direction_cameraspace;

void main() {
	vec4 vertexPosition_cameraspace = u_view * vec4(v_pos.xyz, 1.0);

	vec3 eye_direction = vec3(0) - vertexPosition_cameraspace.xyz;
	light_direction_cameraspace = (u_view * vec4(vec3(0), 1)).xyz + eye_direction;
	normal_cameraspace = (u_view * vec4(v_normal.xyz, 1.0)).xyz;

	f_pos = v_pos;
	f_normal = v_normal;

    gl_Position = u_projection * vertexPosition_cameraspace;
}
