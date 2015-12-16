#pragma once

#include <SDL_image.h>

#include "Shader.h"

class Texture {
public:
	Texture();
	Texture(std::string filename);
	Texture(const Texture& other);
	~Texture();

	GLuint getID() const { return id; }
	bool isLoaded() const { return loaded; }
	void setImage(const std::string& filename);

	Texture& operator=(const Texture& other);

private:
	bool load();
	SDL_Surface* reversePixels(SDL_Surface* source) const;

	GLuint id;
	std::string filename;
	bool loaded;

};

