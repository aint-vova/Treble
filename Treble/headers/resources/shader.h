#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>

namespace Treble
{
	class Shader
	{
	private:
		GLuint m_shaderProgram{};
		bool m_alive{false};
	public:
		Shader(const std::string &vertexPath, const std::string &fragmentPath);
		void use();
		void setUniformMatrix4x4(const std::string &name, const glm::mat4 &matrix) const;
		void setUniformVec(const std::string &name, const glm::vec3 &vector) const;
	};
}
