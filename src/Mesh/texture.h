#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../stb_image.h"
#include <iostream>

class Texture {
public:
	unsigned int id;
	std::string type;
	std::string path;
	Texture();
	Texture(std::string path){
		std::cout << path << std::endl;
		this->path = path;
    // texture 1
    // ---------
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
     // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

		GLenum format;
		if (nrChannels == 1)
				format = GL_RED;
		else if (nrChannels == 3)
				format = GL_RGB;
		else if (nrChannels == 4)
				format = GL_RGBA;
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
	}
};

#endif
