#include "resources/texture.h"

#include "resources/file.h"

#include <stb_image.h>

#include <iostream>

namespace Treble
{
	void Texture::loadFromFile(const std::string &path)
	{
		stbi_set_flip_vertically_on_load(true);

		int width, height, nrChannels;
		unsigned char *data = stbi_load((getExecutableDir().string() + '\\' + path).c_str(), &width, &height, &nrChannels, 0);

		if (!data)
		{
			std::cout << "Failed loading image \"" << path << "\"." << std::endl;
			return;
		}

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

		m_texture = texture;
		m_alive = true;
	}
	void Texture::use() const
	{
		if (!m_alive)
		{
			std::cout << "Tried to use dead texture!" << std::endl;
			return;
		}

		glBindTexture(GL_TEXTURE_2D, m_texture);
	}
}
