#version 420 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec4 vertex_color;

uniform mat4 world;
uniform mat4 perspective;
uniform mat4 camera;

out vec4 position;
out vec4 color;

void main() {

	vec4 camera_space_position = vec4(vertex_position, 1.0) * world;

	gl_Position = camera_space_position * perspective;

	color = vertex_color;
	position = camera_space_position;
}