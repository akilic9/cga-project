#pragma once
#include "ResourceManager.h"
#include "SFML/Graphics/Texture.hpp"

class TextureLoader : public ResourceManager<TextureLoader, sf::Texture>
{
public:
    TextureLoader() : ResourceManager("ResourcePaths.data") {}

    sf::Texture* Load(const std::string& path) override {
        sf::Texture* texture = new sf::Texture();
        if (!texture->loadFromFile(path))
        {
            delete texture;
            texture = nullptr;
        }
        texture->setSmooth(true);
        return texture;
    }
};