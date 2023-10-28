#include "entities/player.h"

#include "core/world.h"

#include <iostream>

namespace Treble
{
	Player::Player(World *world)
		: Entity(world)
	{
	}

	void Player::tick()
	{
		m_world->spawnParticle();
	}

	void Player::render()
	{
		std::cout << "player render\n";
	}
}
