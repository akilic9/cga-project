#pragma once
#include "ResourceManager.h"
#include "SFML/Graphics/Texture.hpp"

class TextureLoader : public ResourceManager<TextureLoader, sf::Texture>
{
public:
    TextureLoader() : ResourceManager("spritesheetPaths.cfg") {}

    sf::Texture* Load(const std::string& path) {
        sf::Texture* texture = new sf::Texture();
        if (!texture->loadFromFile("Resources/" + path))
        {
            delete texture;
            texture = nullptr;
        }
        texture->setSmooth(true);
        return texture;
    }
};