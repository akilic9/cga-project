#pragma once
#include "ResourceManager.h"
#include "SFML/Graphics/Texture.hpp"

class SpriteLoader : public ResourceManager<SpriteLoader, sf::Texture>
{
public:
	SpriteLoader() : ResourceManager("spritesheetPaths.cfg") {}

	sf::Texture* Load(const std::string& path) {
		sf::Texture* texture = new sf::Texture();
		if (!texture->loadFromFile("Resources/" + path))
		{
			delete texture;
			texture = nullptr;
		}
		return texture;
	}
};