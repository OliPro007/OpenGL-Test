#include "Shader.h"

Shader::Shader(std::string vertexSource, std::string fragmentSource) :
vertexID(0), fragmentID(0), programID(0), vertexSource(vertexSource), fragmentSource(fragmentSource) {
	load();
}

Shader::Shader(const Shader& other) {
	this->vertexSource = other.vertexSource;
	this->fragmentSource = other.fragmentSource;

	load();
}

Shader& Shader::operator=(const Shader& other) {
	this->vertexSource = other.vertexSource;
	this->fragmentSource = other.fragmentSource;

	load();

	return *this;
}

Shader::~Shader() {
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
	glDeleteProgram(programID);
}

bool Shader::load() {
	if(glIsShader(vertexID) == GL_TRUE)
		glDeleteShader(vertexID);

	if(glIsShader(fragmentID) == GL_TRUE)
		glDeleteShader(fragmentID);

	if(glIsProgram(programID) == GL_TRUE)
		glDeleteProgram(programID);


	if(!compileShader(vertexID, GL_VERTEX_SHADER, vertexSource))
		return false;

	if(!compileShader(fragmentID, GL_FRAGMENT_SHADER, fragmentSource))
		return false;

	programID = glCreateProgram();
	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);

	glBindAttribLocation(programID, 0, "in_Vertex");
	glBindAttribLocation(programID, 1, "in_Color");
	glBindAttribLocation(programID, 2, "in_TexCoord0");
	glBindAttribLocation(programID, 3, "in_Normal");

	glLinkProgram(programID);
	GLint linkError;
	glGetProgramiv(programID, GL_LINK_STATUS, &linkError);
	if(linkError != GL_TRUE) {
		GLint errorSize;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &errorSize);
		char* error = new char[errorSize + 1];
		glGetProgramInfoLog(programID, errorSize, &errorSize, error);
		error[errorSize] = '\0';
		std::cerr << error << std::endl;
		delete[] error;
		glDeleteProgram(programID);
		return false;
	} else {
		return true;
	}
}

bool Shader::compileShader(GLuint& shader, GLenum type, const std::string& sourceFile) {
	shader = glCreateShader(type);
	if(shader == 0) {
		std::cerr << "Error: Shader type " << type << " doesn't exists" << std::endl;
		//glDeleteShader(shader);
		return false;
	}

	std::ifstream file(sourceFile);
	if(file.fail()) {
		std::cerr << "Error: File " << sourceFile << " not found" << std::endl;
		glDeleteShader(shader);
		return false;
	}

	std::string line;
	std::string code;
	while(!ws(file).eof()) {
		std::getline(file, line);
		code += line + '\n';
	}
	file.close();

	const GLchar* glCode = code.c_str();
	glShaderSource(shader, 1, &glCode, 0);
	glCompileShader(shader);

	GLint compileError;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileError);
	if(compileError != GL_TRUE) {
		GLint errorSize;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorSize);
		char* error = new char[errorSize + 1];
		glGetShaderInfoLog(shader, errorSize, &errorSize, error);
		error[errorSize] = '\0';
		std::cerr << error << std::endl;
		delete[] error;
		glDeleteShader(shader);
		return false;
	} else {
		return true;
	}
}