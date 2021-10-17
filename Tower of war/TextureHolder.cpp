#include "TextureHolder.h"
#include <assert.h>

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder()
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

Texture& TextureHolder::GetTexture(string const& fileName)
{
	auto& m = m_s_Instance->Map_Texture;
	auto keyValuePair = m.find(fileName);

	if (keyValuePair != m.end())
	{
		return keyValuePair->second;
	}
	else
	{
		auto& texture = m[fileName];
		texture.loadFromFile(fileName);
		return texture;
	}
}
