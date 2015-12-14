#version 330 core

in vec3 in_Vertex;
in vec2 in_TexCoord0;
in vec3 in_Normal;

uniform mat4 projection;
uniform mat4 modelview;

uniform vec3 ambiant;
uniform vec3 diffuse;
uniform vec3 specular;
uniform vec3 light;

varying vec4 colorDiffuse;
varying vec4 colorSpecular;
out vec2 texCoord;

void main(){
	gl_Position = projection * modelview * vec4(in_Vertex, 1.0);
	vec3 worldNormal = vec3(mat3(modelview[0].xyz, modelview[1].xyz, modelview[2].xyz) * in_Normal);

	colorDiffuse = dot(worldNormal, normalize(-light + in_Vertex)) * vec4(diffuse, 1.0) + vec4(ambiant, 1.0);

	vec3 halfVector = normalize(in_Vertex - light);
	float NdotH = max(-dot(worldNormal, halfVector), 0.0);
	float fPower = 47.058824;
	float fSpecular = min(pow(NdotH, fPower), 1.0);
	colorSpecular = vec4(specular * fSpecular, 1.0);

	texCoord = in_TexCoord0;
}