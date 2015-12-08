#include "Scene.h"

int main(int argc, char** argv){
	Scene scene("OpenGL Test");

	if(!scene.initWindow())

		return -1;
	if(!scene.initGL())
		return -2;

	scene.mainLoop();

	return 0;
}