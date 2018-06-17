#include "texture.h"
#include <iostream>

Texture::Texture(std::string path, GLenum texture) {
	this->path = path;
	this->texture = texture;

	data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	stbi_set_flip_vertically_on_load(true);
}

void Texture::init() {
	glGenTextures(1, &textureAddress);
	glBindTexture(GL_TEXTURE_2D, textureAddress);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

void Texture::render() {
	glActiveTexture(texture);
	glBindTexture(GL_TEXTURE_2D, textureAddress);
}
