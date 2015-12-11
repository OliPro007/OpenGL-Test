#version 150 core

uniform vec3 ambiant;
uniform vec3 diffuse;
uniform vec3 specular;

void main(){
	gl_FragColor = vec4(ambiant, 1.0) + vec4(diffuse, 1.0) + vec4(specular, 1.0);
}