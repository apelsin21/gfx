#version 130

in vec3 f_pos;
in vec3 f_normal;
in vec3 normal_cameraspace;
in vec3 light_direction_cameraspace;

uniform sampler2D u_sampler;
uniform vec3 u_eye_pos;

void main() {
	// texturing
  	vec3 blend_weights = abs(f_normal);
  	
  	blend_weights = (blend_weights - 0.2) * 7;
  	blend_weights = max(blend_weights, 0);
  	blend_weights /= vec3(blend_weights.x + blend_weights.y + blend_weights.z).xxx;
  
  	vec2 coord1 = f_pos.yz;
  	vec2 coord2 = f_pos.zx;
  	vec2 coord3 = f_pos.xy;
  
  	vec4 col1 = texture2D(u_sampler, coord1);
  	vec4 col2 = texture2D(u_sampler, coord2);
  	vec4 col3 = texture2D(u_sampler, coord3);
  
  	vec4 tex_color = 
		col1.rgba * blend_weights.xxxx +
  		col2.rgba * blend_weights.yyyy +
  		col3.rgba * blend_weights.zzzz
	;

	// shading
	vec3 n = normalize(normal_cameraspace);
	vec3 l = normalize(light_direction_cameraspace);
	float cos_theta = clamp(dot(n, l), 0, 1);
	float distance = length(u_eye_pos - f_pos);

	vec4 light_color = vec4(1, 1, 1, 1.0);
	vec4 ambient_color = vec4(0.1, 0.1, 0.1, 1.0) * tex_color;

	// mixing the above
	gl_FragColor = 
		ambient_color + 
		tex_color * 
		light_color * 
		cos_theta / 
		distance
	;
}
