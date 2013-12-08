#version 420 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec4 vertex_color;

in mat4 model;
in mat4 perspective;
in mat4 view;

out vec4 color;

void main() {

	gl_Position.xyz = vertex_position;
	gl_Position.w = 1.0;

	color = vertex_color;
}