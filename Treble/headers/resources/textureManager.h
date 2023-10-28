#pragma once

#include "texture.h"

#include <string>
#include <unordered_map>

namespace Treble
{
	class TextureManager
	{
	private:
		std::unordered_map<std::string, Texture> m_texturesMap{};
	public:
		void useTexture(const std::string &path);
	};
}
