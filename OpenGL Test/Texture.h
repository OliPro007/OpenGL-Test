#pragma once

#include <SDL_image.h>

#include "Shader.h"

class Texture {
public:
	Texture() = default;
	Texture(std::string filename);
	Texture(const Texture& other);
	~Texture();

	GLuint getID() const { return id; }

	Texture& operator=(const Texture& other);

private:
	bool load();
	SDL_Surface* reversePixels(SDL_Surface* source) const;

	GLuint id;
	std::string filename;

};

