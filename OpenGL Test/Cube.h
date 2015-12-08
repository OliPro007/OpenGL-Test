#pragma once

#include "Shader.h"

using namespace glm;

class Cube {
public:
	Cube(float size, const std::string vertexShader, const std::string fragmentShader);
	~Cube();

	void draw(mat4& projection, mat4& modelview);

private:
	float vertices[6 * 2 * 3][3];
	float colors[6 * 2 * 3][3];
	Shader shader;

};

