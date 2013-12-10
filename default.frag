#version 420

in vec4 position;
in vec4 color;

out vec4 color_out;

void main() {

	//Fog test
	/*color_out = vec4 (
		color.rgb * (1.0 - clamp((-2.0 - position.z) * 0.3, 0.0, 1.0)),
		1.0
	);*/

	color_out = vec4 (color.rgb, 1.0);
}