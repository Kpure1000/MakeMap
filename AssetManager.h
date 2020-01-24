#pragma once
#include<SFML/Graphics.hpp>
#include<map>
#include<string>
#include<iostream>
#include<cassert>
//
#include"Setting.h"
using namespace std;
using namespace sf;
class AssetManager
{
private:
	std::map<std::string, sf::Texture> m_Textures;
	std::map<string, Font>m_Fonts;
	static AssetManager* sInstance;
public:
	AssetManager();
	~AssetManager() {}
	static Font& GetFont(string const& filename);
	static Texture& GetTexture(std::string const& filename);
};

