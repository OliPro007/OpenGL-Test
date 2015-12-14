#version 330 core

varying vec4 colorDiffuse;
varying vec4 colorSpecular;

in vec2 texCoord;
uniform sampler2D tex;

void main(){
	vec4 textureColor = texture(tex, texCoord);
	gl_FragColor = colorDiffuse + colorSpecular;
}