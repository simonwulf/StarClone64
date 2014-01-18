/*
	This is the base vertex shader

	This base shader call approperiate functions 
	defined in other shaders that is part of the 
	same program.

	This shader also handles the default behavior.
*/

#version 420

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_texture_coords;
layout(location = 3) in vec3 vertex_tangent;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec3 world_position;
out vec3 cam_position;
out vec3 world_normal;
out vec3 cam_normal;
out vec3 vert_normal;
out vec2 texture_coords;
out vec3 tangent;

void main() {
	
	vec4 world_space_position = model * vec4(vertex_position, 1.0);
	vec4 cam_space_position = view * world_space_position;
	gl_Position = projection * cam_space_position;

	vec4 world_space_normal = model * vec4(vertex_normal, 0.0);
	world_normal = world_space_normal.xyz;
	cam_normal = (view * world_space_normal).xyz;
	world_position = world_space_position.xyz;
	cam_position = cam_space_position.xyz;

	texture_coords = vertex_texture_coords;
	tangent = vertex_tangent;
	vert_normal = vertex_normal;
}