#include "core/window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace Treble
{
	Window::Window(GLFWwindow *internalWindow)
		:m_internalWindow(internalWindow)
	{
	}

	std::shared_ptr<Window> Window::create(const std::string &title, int width, int height)
	{
		std::cout << "Creating window..." << std::endl;

		if (!glfwInit())
		{
			std::cout << "Failed initializing glfw." << std::endl;
			return nullptr;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow *internalWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

		if (internalWindow == nullptr)
		{
			std::cout << "Failed creating window." << std::endl;
			glfwTerminate();
			return nullptr;
		}

		glfwMakeContextCurrent(internalWindow);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed initializing glad." << std::endl;
			return nullptr;
		}

		auto window{std::shared_ptr<Window>(new Window{internalWindow})};

		glfwSetWindowUserPointer(internalWindow, window.get());

		glfwSetWindowSizeCallback(internalWindow, [](GLFWwindow *internalWindow, int width, int height)
		{
			Window *window{static_cast<Window *>(glfwGetWindowUserPointer(internalWindow))};
			window->resizedWindowCallback(width, height);
		});

		glClearColor(0.2f, 0.7f, 0.8f, 1);

		return window;
	}

	bool Window::shouldClose() const
	{
		return glfwWindowShouldClose(m_internalWindow);
	}

	void Window::resizedWindowCallback(int width, int height)
	{
		m_width = width;
		m_height = height;
		glViewport(0, 0, m_width, m_height);
	}

	void Window::pollEvents() const
	{
		glfwPollEvents();
	}

	void Window::swapBuffers() const
	{
		glfwSwapBuffers(m_internalWindow);
	}

	void Window::clearBuffer()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_internalWindow);
		glfwTerminate();
	}
}
