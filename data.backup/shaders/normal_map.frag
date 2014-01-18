#version 420

uniform mat4 model;
uniform sampler2D normalmap;

in vec2 texture_coords;
in vec3 vert_normal;
in vec3 tangent;

vec3 calculateNormalMap() {
	vec3 _normal = normalize(vert_normal);
	vec3 _tangent = normalize(tangent);
	_tangent = normalize( _tangent - dot(_tangent, _normal) * _normal );
	vec3 _bitangent = cross(_tangent, _normal);
	vec3 _bumpMapNormal = texture(normalmap, texture_coords).xyz;
	_bumpMapNormal = (_bumpMapNormal * 2.0) - vec3(1.0, 1.0, 1.0);
	
	vec3 newNormal;
	vec4 productNormal;
	mat3 tbn = mat3(_tangent, _bitangent, _normal);
	newNormal = tbn * _bumpMapNormal;
	productNormal = model * vec4(newNormal, 0.0);
	newNormal = normalize(vec3(productNormal));
	return newNormal;
}