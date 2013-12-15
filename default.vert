#version 420 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec3 world_position;
out vec3 cam_position;
out vec3 world_normal;
out vec3 cam_normal;

void main() {

	vec4 world_space_position = model * vec4(vertex_position, 1.0);
	vec4 cam_space_position = view * world_space_position;
	gl_Position = projection * cam_space_position;

	vec4 world_space_normal = model * vec4(vertex_normal, 0.0);
	world_normal = world_space_normal.xyz;
	cam_normal = (view * world_space_normal).xyz;
	world_position = world_space_position.xyz;
	cam_position = cam_space_position.xyz;
}