#version 420

in vec3 tangent;
out vec4 color_out;

void testFunc() {
	color_out = normalize(color_out * vec4(tangent, 1.0));
}