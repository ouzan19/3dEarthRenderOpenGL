#version 120

uniform samplerCube cubeMap;

varying vec3 texCoord;

void main (void) {
	gl_FragColor = textureCube(cubeMap, texCoord);
}
