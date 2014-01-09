#version 420

struct DirLight {

	vec3 direction;
	vec3 color;
	float strength;
};

struct PointLight {

	vec3 position;
	float radius;
	vec3 color;
	float strength;
};

layout(std140) uniform DirectionalLights {

	DirLight dir_lights[32];
};

layout(std140) uniform PointLights {

	PointLight point_lights[64];
};

uniform uint dir_light_count;
uniform uint point_light_count;
uniform vec3 ambient_light;

uniform sampler2D diffuse;

in vec3 world_position;
in vec3 cam_position;
in vec3 world_normal;
in vec3 cam_normal;

in vec2 texture_coords;

out vec4 color_out;

void main() {

	//Fog test
	/*color_out = vec4 (
		color.rgb * (1.0 - clamp((-2.0 - position.z) * 0.3, 0.0, 1.0)),
		1.0
	);*/

	vec3 lighting = ambient_light;
	vec3 world_normal = normalize(world_normal);

	float light_wrap = 0.0;

	//Directional lighting test
	/* */
	for (uint i = 0; i < dir_light_count; ++i) {
		
		vec3 light_dir = normalize(dir_lights[i].direction);
		float cos_theta = max((light_wrap + dot(world_normal, -light_dir)) / (1.0 + light_wrap), 0.0);
		
		lighting += dir_lights[i].color * cos_theta * dir_lights[i].strength
			+ dir_lights[i].color * min(pow(cos_theta, 50) * dir_lights[i].strength, 1.0);
	}
	/* */

	//Point lights test
	/* */
	for (uint i = 0; i < point_light_count; i++) {
	
		vec3 diff = world_position - point_lights[i].position;
		float falloff = max(1.0 - length(diff) / point_lights[i].radius, 0.0);

		if (falloff == 0.0)
			continue;

		vec3 light_dir = normalize(diff);
		float cos_theta = max((light_wrap + dot(world_normal, -light_dir)) / (1.0 + light_wrap), 0.0);
		//cos_theta = pow(cos_theta, 2);

		lighting +=
			point_lights[i].color * min(cos_theta * falloff * point_lights[i].strength, 1.0) +
			point_lights[i].color * min(pow(cos_theta, 50) * falloff * point_lights[i].strength, 1.0);

		//Rim light test
		float rim_cos_theta = max(dot(normalize(cam_normal), normalize(-cam_position)), 0.0);
		lighting += point_lights[i].color * pow(max(1.0 - rim_cos_theta, 0.0), 2) * falloff * point_lights[i].strength * (1.0 - cos_theta);
	}
	/* */

	//color_out = vec4(lighting, 1.0) * texture2D(diffuse, texture_coords);
	
	color_out = (vec4(lighting, 1.0) * texture2D(diffuse, texture_coords));// * (1.0 - clamp((-10.0 - cam_position.z) * 0.3, 0.0, 1.0));
	//color_out = vec4(lighting, 1.0);
	//color_out = vec4(normal * light_amount, 1.0);
}