#include "Texture.h"

Texture::Texture(std::string filename):
id(0), filename(filename) {
	load();
}

Texture::Texture(const Texture& other) {
	this->id = other.id;
	this->filename = other.filename;

	load();
}

Texture& Texture::operator=(const Texture& other) {
	this->id = other.id;
	this->filename = other.filename;

	load();

	return *this;
}

Texture::~Texture() {
	glDeleteTextures(1, &id);
}

bool Texture::load() {
	SDL_Surface* image = IMG_Load(filename.c_str());
	if(image == nullptr) {
		std::cerr << "Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_Surface* reversedImage = reversePixels(image);
	SDL_FreeSurface(image);

	if(glIsTexture(id) == GL_TRUE)
		glDeleteTextures(1, &id);

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	GLenum internalFormat = 0;
	GLenum format = 0;
	if(reversedImage->format->BytesPerPixel == 3) {
		internalFormat = GL_RGB;
		if(reversedImage->format->Rmask == 0xff)
			format = GL_RGB;
		else
			format = GL_BGR;
	} else if(reversedImage->format->BytesPerPixel == 4) {
		internalFormat = GL_RGBA;
		if(reversedImage->format->Rmask == 0xff)
			format = GL_RGBA;
		else
			format = GL_BGRA;
	} else {
		std::cerr << "Error: Unrecognized format" << std::endl;
		return false;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, reversedImage->w, reversedImage->h, 0, format, GL_UNSIGNED_BYTE, reversedImage->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	SDL_FreeSurface(reversedImage);
	return true;
}

SDL_Surface* Texture::reversePixels(SDL_Surface* source) const {
	SDL_Surface* reversedImage = SDL_CreateRGBSurface(0, source->w, source->h, source->format->BitsPerPixel, 
													  source->format->Rmask, source->format->Gmask, source->format->Bmask, source->format->Amask);
	
	unsigned char* sourcePixels = (unsigned char*)source->pixels;
	unsigned char* reversedPixels = (unsigned char*)reversedImage->pixels;
	for(int i = 0; i < source->h; i++) {
		for(int j = 0; j < source->w * source->format->BytesPerPixel; j++) {
			reversedPixels[(source->w * source->format->BytesPerPixel * (source->h - 1 - i)) + j] 
				= sourcePixels[(source->w * source->format->BytesPerPixel * i) + j];
		}
	}

	return reversedImage;
}
