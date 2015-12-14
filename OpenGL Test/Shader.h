#pragma once

#ifdef WIN32
#include <GL/glew.h>
#elif __APPLE__
#define GL3_PROTOTYPES 1
#include <OpenGL/gl3.h>
#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#endif

#include <fstream>
#include <iostream>
#include <string>

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