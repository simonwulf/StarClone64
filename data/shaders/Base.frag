/*
	This is the base fragment shader

	This base shader call approperiate functions 
	defined in other shaders that is part of the 
	same program.

	This shader also handles the default behavior (diffuse-map rendering).
*/

#version 420

uniform sampler2D diffuse;

in vec3 world_normal;
in vec2 texture_coords;

out vec4 color_out;

void calculateLightingDiffuse(vec3 _world_normal);
void testFunc();
vec3 calculateNormalMap();

void main() {
	
	vec3 _world_normal = world_normal;

	color_out = texture2D(diffuse, texture_coords);

	#ifdef SHADER_NORMAL_MAP
		_world_normal = calculateNormalMap();
	#endif

	#ifdef SHADER_LIGHTING_DIFFUSE
		calculateLightingDiffuse(_world_normal);
	#endif

	#ifdef SHADER_ALPHA_MASK
	#endif
}