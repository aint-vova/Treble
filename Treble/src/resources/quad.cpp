#include "resources/quad.h"

namespace Treble
{
	Quad::Quad()
	{
		constexpr GLfloat positionsSource[]{
			0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
		};

		constexpr GLfloat uvsSource[]{
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f,
		};

		GLuint positionsVbo{};
		glGenBuffers(1, &positionsVbo);
		glBindBuffer(GL_ARRAY_BUFFER, positionsVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(positionsSource), positionsSource, GL_STATIC_DRAW);

		m_positionsVbo = positionsVbo;

		GLuint uvsVbo{};
		glGenBuffers(1, &uvsVbo);
		glBindBuffer(GL_ARRAY_BUFFER, uvsVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uvsSource), uvsSource, GL_STATIC_DRAW);

		m_uvsVbo = uvsVbo;

		GLuint vao{};
		glCreateVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, positionsVbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, static_cast<void*>(nullptr));
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, uvsVbo);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, static_cast<void*>(nullptr));
		glEnableVertexAttribArray(1);

		m_vao = vao;
	}

	Quad::~Quad()
	{
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_uvsVbo);
		glDeleteBuffers(1, &m_positionsVbo);
	}

	void Quad::draw() const
	{
		glBindVertexArray(m_vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}
