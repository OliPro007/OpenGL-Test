#version 150 core

out vec4 out_Color;

uniform vec3 diffuse;

void main(){
	out_Color = vec4(diffuse, 1.0);
}