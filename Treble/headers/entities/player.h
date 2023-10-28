#pragma once

#include "entity.h"

namespace Treble
{
	class Player : public Entity
	{
	public:
		explicit Player(World *world);
		void tick() override;
		void render() override;
	};
}
