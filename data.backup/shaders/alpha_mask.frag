#version 420

void alphaMask(vec4 colorvec) {
	if(colorvec.a == 0.0) discard;
}