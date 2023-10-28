#include "core/world.h"

#include "entities/player.h"

#include <iostream>

namespace Treble
{
	void World::spawnPlayer()
	{
		m_entities.push_back(std::make_shared<Player>(this));
	}

	void World::spawnParticle() const
	{
		std::cout << "SPAWNED PARTICLE\n";
	}

	void World::tick()
	{
		for (const auto &entity : m_entities)
		{
			entity->tick();
		}
	}
	void World::render()
	{
		for (const auto &entity : m_entities)
		{
			entity->render();
		}
	}
}
