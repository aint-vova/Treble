#include "core/engine.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <glm/gtc/type_ptr.hpp>

namespace Treble
{
	void Engine::createWindow(const std::string& windowTitle, int windowWidth, int windowHeight)
	{
		std::cout << "Starting engine..." << std::endl;

		if (!glfwInit())
		{
			std::cout << "Failed initializing glfw." << std::endl;
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_windowWidth = windowWidth;
		m_windowHeight = windowHeight;

		GLFWwindow *window = glfwCreateWindow(m_windowWidth, m_windowHeight, windowTitle.c_str(), nullptr, nullptr);

		if (window == nullptr)
		{
			std::cout << "Failed creating window." << std::endl;
			glfwTerminate();
			return;
		}

		m_window = window;

		glfwMakeContextCurrent(window);

		glfwSetWindowUserPointer(window, this);

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow *window, int width, int height)
		{
			Engine *engine{static_cast<Engine *>(glfwGetWindowUserPointer(window))};
			engine->resizedWindowCallback(width, height);
		});

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed initializing glad." << std::endl;
			return;
		}

		glClearColor(0.2f, 0.2f, 0.2f, 1);

		m_previousFrameTime = glfwGetTime();

		m_defaultShader = std::make_unique<Shader>("shaders/sus.vert", "shaders/sus.frag");
		m_textureManager = std::make_unique<TextureManager>();
		m_quad = std::make_unique<Quad>();

		glfwSwapInterval(0);
	}

	void Engine::loadDefaultShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		m_defaultShader = std::make_unique<Shader>(vertexShaderPath, fragmentShaderPath);
	}

	void Engine::destroyWindow()
	{
		glfwTerminate();
		m_window = nullptr;
	}

	void Engine::resizedWindowCallback(int newWidth, int newHeight)
	{
		m_windowWidth = newWidth;
		m_windowHeight = newHeight;
		glViewport(0, 0, m_windowWidth, m_windowHeight);
	}

	bool Engine::windowShouldClose()
	{
		return glfwWindowShouldClose(m_window);
	}

	void Engine::pollEvents()
	{
		glfwPollEvents();
	}

	void Engine::swapBuffers() const
	{
		glfwSwapBuffers(m_window);
	}

	void Engine::clearWindow()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	bool Engine::isKeyDown(int key) const
	{
		return glfwGetKey(m_window, key) == GLFW_PRESS;
	}

	bool Engine::isMouseDown(int key) const
	{
		return glfwGetMouseButton(m_window, key) == GLFW_PRESS;
	}

	void Engine::drawImage(const std::string &imagePath, const glm::vec2 &position, const glm::vec2 &size) const
	{
		m_defaultShader->use();

		glm::mat4 model{1.0f};
		model = glm::translate(model, glm::vec3{position.x, position.y, 0.0f});
		model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));

		// TODO: integer-ize translation and possibly scale too

		glm::mat4 view{1.0f};

		glm::mat4 projection{glm::ortho(0.0f, static_cast<float>(m_windowWidth), 0.0f, static_cast<float>(m_windowHeight))};

		glm::mat4 mvp{projection * view * model};

		m_defaultShader->setUniformMatrix4x4("mvp", mvp);
		m_defaultShader->setUniformVec("color", glm::vec3(1.0f, 1.0f, 1.0f));

		m_textureManager->useTexture(imagePath);

		m_quad->draw();
	}

	void Engine::drawImageColored(const std::string &imagePath, const glm::vec2 &position, const glm::vec2 &size,
		const glm::vec3 &color) const
	{
		m_defaultShader->use();

		glm::mat4 model{1.0f};
		model = glm::translate(model, glm::vec3{position.x, position.y, 0.0f});
		model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));

		glm::mat4 view{1.0f};

		glm::mat4 projection{glm::ortho(0.0f, static_cast<float>(m_windowWidth), 0.0f, static_cast<float>(m_windowHeight))};

		glm::mat4 mvp{projection * view * model};

		m_defaultShader->setUniformMatrix4x4("mvp", mvp);
		m_defaultShader->setUniformVec("color", color);

		m_textureManager->useTexture(imagePath);

		m_quad->draw();
	}

	int Engine::getWindowWidth() const
	{
		return m_windowWidth;
	}

	int Engine::getWindowHeight() const
	{
		return m_windowHeight;
	}

	glm::vec2 Engine::getWindowSize() const
	{
		return {static_cast<float>(m_windowWidth), static_cast<float>(m_windowHeight)};
	}

	glm::vec2 Engine::getVectorFromButtons(int leftButton, int rightButton, int downButton, int upButton) const
	{
		glm::vec2 result{};
		if (isKeyDown(leftButton)) { result += glm::vec2(-1.0f, 0.0f); }
		if (isKeyDown(rightButton)) { result += glm::vec2(1.0f, 0.0f); }
		if (isKeyDown(downButton)) { result += glm::vec2(0.0f, -1.0f); }
		if (isKeyDown(upButton)) { result += glm::vec2(0.0f, 1.0f); }
		return result;
	}

	float Engine::time() const
	{
		return static_cast<float>(glfwGetTime());
	}

	float Engine::deltaTime() const
	{
		return static_cast<float>(m_deltaTime);
	}

	void Engine::processDeltaTime()
	{
		m_deltaTime = glfwGetTime() - m_previousFrameTime;
		m_previousFrameTime = glfwGetTime();
	}

	glm::vec2 Engine::getMousePosition() const
	{
		double posX{}, posY{};
		glfwGetCursorPos(m_window, &posX, &posY);
		return {static_cast<float>(posX), static_cast<float>(m_windowHeight) - static_cast<float>(posY)};
	}
}
