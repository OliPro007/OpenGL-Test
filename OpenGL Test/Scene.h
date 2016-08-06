#pragma once

#include <iostream>
#include <string>

#include <SDL.h>
#include <GL/glew.h>

#include "Cube.h"
#include "EventManager.h"

#ifdef LINUXRELEASE //Define standard install location
#define ROOT "/usr/share/opengl-test/"
#else
#define ROOT "./"
#endif

#define ICON                ROOT "icon.bmp"
#define DODECAHEDRON_OBJ    ROOT "dodecahedron.obj"
#define DODECAHEDRON_MTL    ROOT "dodecahedron.mtl"
#define DODECAHEDRON_VERT   ROOT "dodecahedron.vert"
#define DODECAHEDRON_FRAG   ROOT "dodecahedron.frag"

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

