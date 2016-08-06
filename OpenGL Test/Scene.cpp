#include "Scene.h"
#include "Model.h"

using namespace glm;

Scene::Scene(std::string title, int width, int height) :
title(title), width(width), height(height), eventManager() {}

Scene::~Scene() {
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Scene::initWindow() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	
	window = SDL_CreateWindow("OpenGL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if(window == nullptr) {
		std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

	SDL_Surface* icon = SDL_LoadBMP(ICON);
	if(icon == nullptr) {
		std::cerr << "Error loading icon" << std::endl;
	} else {
		SDL_SetWindowIcon(window, icon);
		SDL_FreeSurface(icon);
	}

	return true;
}

bool Scene::initGL() {
	glContext = SDL_GL_CreateContext(window);
	if(glContext == 0) {
		std::cerr << "Error creating OpenGl context: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}

	glewExperimental = true;
	GLenum initGLEW(glewInit());
	if(initGLEW != GLEW_OK) {
		std::cerr << "Error initializing GLEW: " << glewGetErrorString(initGLEW) << std::endl;
		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return false;
	}

	glEnable(GL_DEPTH_TEST);

	return true;
}

void Scene::mainLoop() {
	unsigned fps = 1000 / 60;

	mat4 projection;
	projection = perspective(70.0, (double)width / height, 1.0, 100.0);
	mat4 modelview = mat4(1.0);

	//Cube cube(2.0, "cube.vert", "cube.frag");
	float angleX = 0.0;
	float angleY = 0.0;

	Model model(DODECAHEDRON_OBJ, DODECAHEDRON_MTL, DODECAHEDRON_VERT, DODECAHEDRON_FRAG);

	while(!eventManager.hasEnded()) {
		Uint32 beginTick = SDL_GetTicks();

		eventManager.updateEvents();
		if(eventManager.isKeyPressed(SDL_SCANCODE_ESCAPE))
			break;

		if(eventManager.isKeyPressed(SDL_SCANCODE_LEFT)) {
			angleY -= 1.0;
			if(angleY < 0.0)
				angleY += 360.0;
		}
		if(eventManager.isKeyPressed(SDL_SCANCODE_RIGHT)) {
			angleY += 1.0;
			if(angleY > 360.0)
				angleY -= 360.0;
		}
		if(eventManager.isKeyPressed(SDL_SCANCODE_UP)) {
			angleX += 1.0;
			if(angleX > 360.0)
				angleX -= 360.0;
		}
		if(eventManager.isKeyPressed(SDL_SCANCODE_DOWN)) {
			angleX -= 1.0;
			if(angleX < 360.0)
				angleX += 360.0;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		modelview = lookAt(vec3(10, 10, 10), vec3(0, 0, 0), vec3(0, 1, 0));

		/*mat4 save = modelview;
			modelview = rotate(modelview, angleY, vec3(0, 1, 0));
			modelview = rotate(modelview, angleX, vec3(1, 0, 0));
			cube.draw(projection, modelview);
		modelview = save;*/

		mat4 save = modelview;
			modelview = rotate(modelview, angleY, vec3(0, 1, 0));
			modelview = rotate(modelview, angleX, vec3(1, 0, 0));
			model.draw(projection, modelview);
		modelview = save;

		SDL_GL_SwapWindow(window);
		Uint32 endTick = SDL_GetTicks();
		Uint32 elapsed = endTick - beginTick;
		if(elapsed < fps)
			SDL_Delay(fps - elapsed);
	}
}
