#pragma once
#include "SharedContext.h"
#include <SFML/Graphics/Sprite.hpp>

struct TileInfo {

    TileInfo(SharedContext* sContext, const std::string& path = "", unsigned int tileId = 0)
        : m_context(sContext)
        , m_spriteId(0)
        , m_walkable(true)
        , m_destructible(true)
        , m_spriteName("")
    {
        TextureLoader* tmgr = sContext->m_textureLoader;

        if (l_texture == "") {
            m_id = l_id;
            return;
        }

        if (!tmgr->RequireResource(l_texture)) { return; }
        m_texture = l_texture;
        m_id = l_id;
        m_sprite.setTexture(*tmgr->GetResource(m_texture));
        sf::IntRect tileBoundaries(m_id % (Sheet::Sheet_Width / Sheet::Tile_Size) * Sheet::Tile_Size,
                                   m_id / (Sheet::Sheet_Height / Sheet::Tile_Size) * Sheet::Tile_Size,
                                   Sheet::Tile_Size, Sheet::Tile_Size);
        m_sprite.setTextureRect(tileBoundaries);
    }
    ~TileInfo() {
        if (m_texture == "") { return; }
        m_context->m_textureManager->ReleaseResource(m_texture);
    }

    sf::Sprite m_sprite;
    unsigned int m_spriteId;
    std::string m_spriteName;
    bool m_walkable;
    bool m_destructible;
    SharedContext* m_context;
};

class Map
{
};

