#version 330 core

in vec3 f_pos;
in vec3 f_normal;

//in vec3 f_normal_worldspace;
//in vec3 f_normal_cameraspace;

uniform sampler2D u_sampler;
uniform float u_time;

vec4 lightColor = vec4(1, 0, 0, 1);
vec3 lightPosition = vec3(0, 0, 0);

float textureScale = 1.0;

void main() {
  	vec3 blend_weights = abs(f_normal);
  	
  	blend_weights = (blend_weights - 0.2) * 7;
  	blend_weights = max(blend_weights, 0);
  	blend_weights /= vec3(blend_weights.x + blend_weights.y + blend_weights.z).xxx;
  
  	vec2 coord1 = f_pos.yz * textureScale * sin(u_time) + cos(u_time);
  	vec2 coord2 = f_pos.zx * textureScale * sin(u_time) + cos(u_time);
  	vec2 coord3 = f_pos.xy * textureScale * sin(u_time) + cos(u_time);
  
  	vec4 col1 = texture2D(u_sampler, coord1);
  	vec4 col2 = texture2D(u_sampler, coord2);
  	vec4 col3 = texture2D(u_sampler, coord3);
  
  	gl_FragColor = 
		col1.rgba * blend_weights.xxxx +
  		col2.rgba * blend_weights.yyyy +
  		col3.rgba * blend_weights.zzzz
	;
}
