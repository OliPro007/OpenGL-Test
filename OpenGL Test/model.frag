#version 330 core

varying vec4 colorDiffuse;
varying vec4 colorSpecular;

void main(){
	gl_FragColor = colorDiffuse + colorSpecular;
}