#pragma once

#include <SDL.h>

#ifdef WIN32
#include <GL/glew.h>
#elif __APPLE__
#define GL_GLEXT_PROTOTYPES 1
#include <OpenGL/gl3.h>
#else
#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glext.h>
#endif

#include <iostream>
#include <string>

#include "Cube.h"
#include "EventManager.h"

class Scene {
public:
	Scene(std::string title = "", int width = 640, int height = 480);
	~Scene();

	bool initWindow();
	bool initGL();
	void mainLoop();

private:
	std::string title;
	int width;
	int height;

	SDL_Window* window;
	SDL_GLContext  glContext;
	EventManager eventManager;
	
};

