#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>
#include <GL/glew.h>
#include "stb_image.h"
#include <experimental/filesystem>

class Texture {

	unsigned int textureAddress;
	int width, height, nrChannels;
	unsigned char *data;
	std::string path;
	GLenum texture;


public:
	Texture(std::string path, GLenum texture);
	void render();
	void init();

};

#endif
