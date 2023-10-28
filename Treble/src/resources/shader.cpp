#include "resources/shader.h"

#include "resources/file.h"

#include <glm/gtc/type_ptr.hpp>

#include <iostream>

namespace Treble
{
	Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
	{
		std::string vertexShaderCode{fileToString(vertexPath)};
		if (vertexShaderCode.empty())
		{
			std::cout << "Vertex shader code is empty!" << std::endl;
			return;
		}
		std::string fragmentShaderCode{fileToString(fragmentPath)};
		if (fragmentShaderCode.empty())
		{
			std::cout << "Fragment shader code is empty!" << std::endl;
			return;
		}

		GLuint vertexShader{glCreateShader(GL_VERTEX_SHADER)};
		const char *vertexCodeCString{vertexShaderCode.c_str()};
		glShaderSource(vertexShader, 1, &vertexCodeCString, NULL);
		glCompileShader(vertexShader);

		int  success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "Failed to compile vertex shader: " << infoLog << std::endl;
			return;
		}

		GLuint fragmentShader{glCreateShader(GL_FRAGMENT_SHADER)};
		const char *fragmentCodeCString{fragmentShaderCode.c_str()};
		glShaderSource(fragmentShader, 1, &fragmentCodeCString, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "Failed to compile fragment shader: " << infoLog << std::endl;
			return;
		}

		GLuint shaderProgram{glCreateProgram()};
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "Failed to compile fragment shader: " << infoLog << std::endl;
			return;
		}

		m_shaderProgram = shaderProgram;
		m_alive = true;

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	void Shader::use()
	{
		if (m_alive)
		{
			glUseProgram(m_shaderProgram);
		}
		else
		{
			std::cout << "Tried to use dead shader!\n";
		}
	}

	void Shader::setUniformMatrix4x4(const std::string &name, const glm::mat4 &matrix) const
	{
		const int uniformLocation = glGetUniformLocation(m_shaderProgram, name.c_str());
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void Shader::setUniformVec(const std::string &name, const glm::vec3 &vector) const
	{
		const int uniformLocation = glGetUniformLocation(m_shaderProgram, name.c_str());
		glUniform3f(uniformLocation, vector.x, vector.y, vector.z);
	}
}
