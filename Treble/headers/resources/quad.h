#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Treble
{
	class Quad
	{
	private:
		GLuint m_positionsVbo{};
		GLuint m_uvsVbo{};
		GLuint m_vao{};
	public:
		Quad();
		~Quad();
		void draw() const;
	};
}
