#pragma once

#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;

class TextureHolder
{
private:

	map<string, Texture> Map_Texture;
	static TextureHolder* m_s_Instance;

public:

	TextureHolder();
	static Texture& GetTexture(string const& fileName);
	
};

