#pragma once

#include <memory>
#include <vector>

namespace Treble
{
	class Entity;

	class World
	{
	private:
		std::vector<std::shared_ptr<Entity>> m_entities{};
	public:
		void spawnPlayer();
		void spawnParticle() const;
		void tick();
		void render();
	};
}