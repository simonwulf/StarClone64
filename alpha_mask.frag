#version 420

out vec3 color_out;

void alphaMask() {
	if(color_out.a == 0.0) discard;
}