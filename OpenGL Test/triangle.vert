#version 150 core

in vec3 in_Vertex;
in vec3 in_Color;

uniform float fov;
uniform float aspect;
uniform float zNear;
uniform float zFar;
uniform mat4 transforms[20];
uniform int nTransforms;

out vec3 color;

mat4 createProjection(){
	float f = 1 / tan(fov / 2);
	float projection33 = (zFar + zNear) / (zNear - zFar);
	float projection34 = (2 * zFar * zNear) / (zNear - zFar);

	mat4 projection;
	projection[0] = vec4((f / aspect), 0.0, 0.0, 0.0);
	projection[1] = vec4(0.0, f, 0.0, 0.0);
	projection[2] = vec4(0.0, 0.0, projection33, projection34);
	projection[3] = vec4(0.0, 0.0, -1.0, 0.0);

	return projection;
}

mat4 createModelView(){
	mat4 model = mat4(1.0);
	mat4 view = mat4(1.0);
	for(int i = 0; i < nTransforms; i++){
		view *= transforms[i];
	}	
	mat4 modelview = view * model;
	return modelview;
}

void main(){
	mat4 projection = createProjection();

	mat4 modelview = createModelView();

	gl_Position = projection * modelview * vec4(in_Vertex, 1.0);
	color = in_Color;
}
