#pragma once
#include<glad\glad.h>
#include<GLFW\glfw3.h>
#include<iostream>
#include"stb_image.h"

class Texture {
	GLuint id;
	int width, height, nrChannels;
	GLenum type, channels{GL_RGBA};
public:
	Texture(const char* fileName, GLenum type) :type(type) {
		glGenTextures(1, &id);
		glBindTexture(type, id);

		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		stbi_set_flip_vertically_on_load(true);

		unsigned char* data = stbi_load(fileName, &width, &height, &nrChannels, 0);
		if (nrChannels == 1)
			channels = GL_RED;
		else if (nrChannels == 3)
			channels = GL_RGB;
		else if (nrChannels == 4)
			channels = GL_RGBA;
		if (data) {
			glTexImage2D(type, 0, channels, width, height, 0, channels, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(type);
		}
		else {
			std::cout << "Failed to load texture " << fileName << std::endl;
		}
		stbi_image_free(data);
	}

	void bind(GLint texture_unit) {
		glActiveTexture(GL_TEXTURE0 + texture_unit);
		glBindTexture(type, id);
	}

	void unbind() {
		glActiveTexture(0);
		glBindTexture(type, 0);

	}
	GLuint getID() const {
		return id;
	}

	~Texture() {
		glDeleteTextures(1, &id);
	}
};