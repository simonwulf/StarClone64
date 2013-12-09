#version 420 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec4 vertex_color;

uniform mat4 world;
uniform mat4 perspective;
uniform mat4 view;

out vec4 color;

void main() {

	gl_Position = vec4(vertex_position, 1.0) * world * perspective;

	color = vertex_color;
}