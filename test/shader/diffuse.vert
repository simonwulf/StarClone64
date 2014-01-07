#version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 tangent;
layout(location = 3) in vec3 color;
layout(location = 4) in vec2 uv;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

layout(location = 0) out vec3 world_position;
layout(location = 1) out vec3 cam_position;
layout(location = 2) out vec3 world_normal;
layout(location = 3) out vec3 cam_normal;
layout(location = 4) out vec3 out_color;
layout(location = 5) out vec2 out_uv;

void main() {

	vec4 world_space_position = model * vec4(position, 1.0);
	vec4 cam_space_position = view * world_space_position;
	gl_Position = projection * cam_space_position;

	vec4 world_space_normal = model * vec4(normal, 0.0);
	world_normal = world_space_normal.xyz;
	cam_normal = (view * world_space_normal).xyz;
	world_position = world_space_position.xyz;
	cam_position = cam_space_position.xyz;

	out_color = color;
	out_uv = uv;
}