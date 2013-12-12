#version 420 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec4 vertex_color;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec4 position;
out vec4 color;

void main() {

	vec4 camera_space_position = view * model * vec4(vertex_position, 1.0);
	gl_Position = projection * camera_space_position;

	color = vertex_color;
	position = camera_space_position;
}