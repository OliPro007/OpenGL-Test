#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include <GL/glew.h>

#include <glm.hpp>
#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

class Shader {
public:
	Shader(std::string vertexSource = "", std::string fragmentSource = "");
	Shader(const Shader& other);
	~Shader();

	GLuint getProgramID() const { return programID; }

	Shader& operator=(const Shader& other);

private:
	bool load();
	bool compileShader(GLuint& shader, GLenum type, const std::string& sourceFile);

	GLuint vertexID;
	GLuint fragmentID;
	GLuint programID;

	std::string vertexSource;
	std::string fragmentSource;

};
