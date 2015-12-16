#version 330 core

varying vec4 colorDiffuse;
varying vec4 colorSpecular;

in vec2 texCoord;
uniform sampler2D tex;

void main(){
	vec4 textureColor = texture2D(tex, texCoord);
	//gl_FragColor = textureColor;
	//gl_FragColor = colorDiffuse + colorSpecular;
	if(textureColor.rgb == vec3(1.0, 1.0, 1.0)){
		gl_FragColor = textureColor;
	}else{
		gl_FragColor = colorDiffuse + colorSpecular;
	}
}