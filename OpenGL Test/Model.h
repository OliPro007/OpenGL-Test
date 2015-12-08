#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Shader.h"

using namespace glm;

class Material {
public:
	Material(const std::string name): name(name) {}
	~Material() {}

	std::string getName() const { return name; }
	vec3 getAmbiant() const { return ka; }
	vec3 getDiffuse() const { return kd; }
	vec3 getSpecular() const { return ks; }
	float getSpecularExponent() const { return ns; }
	float getRefraction() const { return ni; }
	float getDissolve() const { return d; }
	int getIllum() const { return illum; }

	void setAmbiant(const vec3& ka) { this->ka = ka; }
	void setDiffuse(const vec3& kd) { this->kd = kd; }
	void setSpecular(const vec3& ks) { this->ks = ks; }
	void setSpecularExponent(float ns) { this->ns = ns; }
	void setRefraction(float ni) { this->ni = ni; }
	void setDissolve(float d) { this->d = d; }
	void setIllum(int illum) { this->illum = illum; }

private:
	std::string name;
	vec3 ka;
	vec3 kd;
	vec3 ks;
	float ns;
	float ni;
	float d;
	int illum;

};

class Model {
public:
	Model(const std::string obj, const std::string mtl, const std::string vertexShader, const std::string fragmentShader);
	~Model();

	void draw(mat4& projection, mat4& modelview);

private:
	void readMTL(const std::string path);
	void loadVBO();

	std::vector<vec3> vertices;
	std::vector<vec3> faces;
	std::vector<vec3> normals;
	std::vector<vec2> uvs;
	std::vector<Material> materials;

	Shader shader;
	GLuint vboID;

};
