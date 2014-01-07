#version 420 core

layout(location = 0) in vec3 world_position;
layout(location = 1) in vec3 cam_position;
layout(location = 2) in vec3 world_normal;
layout(location = 3) in vec3 cam_normal;
layout(location = 4) in vec3 color;
layout(location = 5) in vec2 uv;

layout(location = 0) out vec4 out_color;

void main() {
	out_color = vec4(color, 1.0);
}