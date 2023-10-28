#pragma once

namespace Treble
{
	class World;

	class Entity
	{
	protected:
		World *m_world;
	public:
		explicit Entity(World *world);
		virtual ~Entity() = default;
		World *getWorld() const;
		virtual void tick() = 0;
		virtual void render() = 0;
	};
}
