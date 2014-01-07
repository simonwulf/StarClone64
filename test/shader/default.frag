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

in vec3 world_position;
in vec3 cam_position;
in vec3 world_normal;
in vec3 cam_normal;

out vec4 color_out;

void main() {

	//Fog test
	/*color_out = vec4 (
		color.rgb * (1.0 - clamp((-2.0 - position.z) * 0.3, 0.0, 1.0)),
		1.0
	);*/

	vec3 color = vec3(0.0);

	//Directional lighting test
	/* */
	for (uint i = 0; i < dir_light_count; ++i) {
		
		vec3 light_dir = normalize(dir_lights[i].direction);
		float cos_theta = max(dot(normalize(world_normal), -light_dir), 0.0);
		
		color += dir_lights[i].color * cos_theta * dir_lights[i].strength
			+ vec3(1.0, 1.0, 0.0) * pow(cos_theta, 50);
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
		float cos_theta = max(dot(normalize(world_normal), -light_dir), 0.0);

		color +=
			point_lights[i].color * min(cos_theta * falloff * point_lights[i].strength, 1.0) +
			point_lights[i].color * min(pow(cos_theta, 50.0) * falloff * point_lights[i].strength, 1.0);

		//Rim light test
		//cos_theta = max(dot(normalize(cam_normal), normalize(-cam_position)), 0.0);
		//color += point_lights[i].color * max(1.0 - cos_theta * 2.0, 0.0) * falloff * point_lights[i].strength;
	}
	/* */

	color_out = vec4(color, 1.0);
	//color_out = vec4(normal * light_amount, 1.0);
}