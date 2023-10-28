#pragma once

#include "resources/quad.h"
#include "resources/shader.h"
#include "resources/textureManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <string>
#include <unordered_map>

namespace Treble
{
	class Engine
	{
	private:
		GLFWwindow*						m_window{};
		int								m_windowWidth{};
		int								m_windowHeight{};
		std::unique_ptr<TextureManager>	m_textureManager{};
		std::unique_ptr<Shader>			m_defaultShader{};
		std::unique_ptr<Quad>			m_quad{};
		double							m_previousFrameTime{};
		double							m_deltaTime{};
	public:
		std::unordered_map<int, int>	pizdec{};
		void createWindow(const std::string &windowTitle, int windowWidth, int windowHeight);
		void loadDefaultShader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
		void destroyWindow();
		void resizedWindowCallback(int newWidth, int newHeight);
		bool windowShouldClose();
		void pollEvents();
		void swapBuffers() const;
		void clearWindow();
		bool isKeyDown(int key) const;
		bool isMouseDown(int key) const;
		void drawImage(const std::string &imagePath, const glm::vec2 &position, const glm::vec2 &size) const;
		void drawImageColored(const std::string &imagePath, const glm::vec2 &position, const glm::vec2 &size, const glm::vec3 &color) const;
		int getWindowWidth() const;
		int getWindowHeight() const;
		glm::vec2 getWindowSize() const;
		glm::vec2 getVectorFromButtons(int leftButton, int rightButton, int downButton, int upButton) const;
		float time() const;
		float deltaTime() const;
		void processDeltaTime();
		glm::vec2 getMousePosition() const;
	};
;}
