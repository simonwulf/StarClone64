#version 420

in vec4 color;

out vec3 color_frag;

void main() {

	color_frag = color.rgb;
}