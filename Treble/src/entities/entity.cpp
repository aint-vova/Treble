#include "entities/entity.h"

namespace Treble
{
	Entity::Entity(World *world)
		:m_world(world)
	{
	}

	World *Entity::getWorld() const
	{
		return m_world;
	}
}
