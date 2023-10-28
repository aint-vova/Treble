#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace Treble
{
	class Texture
	{
	private:
		GLuint m_texture{};
		bool m_alive{false};
	public:
		void loadFromFile(const std::string &path);
		void use() const;
	};
}
