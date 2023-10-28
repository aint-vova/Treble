#include "core/world.h"
#include "core/window.h"

#include <iostream>

int main()
{
	std::shared_ptr window{Treble::Window::create("Super Duper Window!", 640, 480)};

	if (!window)
	{
		return -1;
	}

	Treble::World world{};

	world.spawnPlayer();

	while (!window->shouldClose())
	{
		window->pollEvents();

		world.tick();

		window->clearBuffer();

		world.render();

		window->swapBuffers();
	}

	window.reset();
	
	return 0;
}