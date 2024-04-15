#pragma once
#include "SharedContext.h"
#include <SFML/Graphics/Sprite.hpp>

struct TileInfo {

    TileInfo(SharedContext* sContext, const std::string& textureId,
             const sf::Vector2u& tileLocation = sf::Vector2u(0, 0), unsigned int tileId)
        : m_context(sContext)
        , m_spriteName("")
        , m_isWalkable(true)
        , m_isDestructible(false)
        , m_isBase(false)
        , m_tileLocation(tileLocation)
    {
        TextureLoader* texLoader = sContext->m_textureLoader;
        
        if (textureId == "" || !texLoader->AllocateResource(textureId))
            return;

        m_tileId = tileId;
        m_textureId = textureId;
        m_sprite.setTexture(*texLoader->GetResource(textureId));
        
        //sf::IntRect
    }

    ~TileInfo() {
        if (m_textureId == "")
            return;

        m_context->m_textureLoader->ReleaseResource(m_textureId);
    }


    sf::Sprite m_sprite;
    std::string m_spriteName;
    std::string m_textureId;
    bool m_isWalkable;
    bool m_isDestructible;
    bool m_isBase;
    sf::Vector2u m_tileLocation;
    SharedContext* m_context;
    unsigned int m_tileId;
};

using TileSet = std::unordered_map<unsigned int, TileInfo*>;

class Map
{
};

