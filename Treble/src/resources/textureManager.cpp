#include "resources/textureManager.h"

namespace Treble
{
	void TextureManager::useTexture(const std::string &path)
	{
		if (m_texturesMap.contains(path))
		{
			m_texturesMap[path].use();
		}
		else
		{
			Texture texture{};
			texture.loadFromFile(path);
			m_texturesMap[path] = texture;
			m_texturesMap[path].use();
		}
	}
}