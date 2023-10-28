#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <string>

namespace Treble
{
	class Window
	{
	private:
		int m_width{};
		int m_height{};
		GLFWwindow *m_internalWindow{};
		Window(GLFWwindow *internalWindow);
	public:
		static std::shared_ptr<Window> create(const std::string &title, int width, int height);
		bool shouldClose() const;
		void pollEvents() const;
		void swapBuffers() const;
		void clearBuffer();
		~Window();
		void resizedWindowCallback(int width, int height);
	};
}
