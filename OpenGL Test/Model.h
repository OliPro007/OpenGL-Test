#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Shader.h"
#include "Texture.h"

#ifdef LINUXRELEASE //Define standard install location
#define ROOT "/usr/share/opengl-test/"
#else
#define ROOT "./"
#endif

using namespace glm;

struct Material {
	std::string name;
	vec3 ka;
	vec3 kd;
	vec3 ks;
	float ns;
	float ni;
	float d;
	int illum;
	Texture texture;
};

class Model {
public:
	Model(const std::string obj, const std::string mtl, const std::string vertexShader, const std::string fragmentShader);
	~Model();

	void draw(mat4& projection, mat4& modelview);
	void updateVBO(void* data, int size, int offset);

private:
	void readMTL(const std::string path);
	void loadBuffers();

	std::vector<vec3> vertices;
	std::vector<vec3> faces;
	std::vector<vec3> normals;
	std::vector<vec2> uvs;
	Material material;

	Shader shader;
	GLuint vboID;
	GLuint vaoID;

};
