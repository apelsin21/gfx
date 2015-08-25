#version 330 core

in vec3 v_pos;
in vec3 v_normal;

uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 f_pos;
out vec3 f_normal;
//out vec3 f_normal_cameraspace;
//out vec3 f_eye_direction_cameraspace;
//out vec3 f_light_direction_cameraspace;

void main() {
    gl_Position = u_projection * u_view * vec4(v_pos.xyz, 1.0);

	f_pos = v_pos;
	f_normal = v_normal;
}
