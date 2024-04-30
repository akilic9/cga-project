#pragma once
#include <unordered_map>
#include <SFML/Graphics/Sprite.hpp>
#include "SharedContext.h"

struct SheetInfo {
    sf::Vector2u m_sheetSize;
    sf::Vector2u m_tileSize;
};

struct TileInfo {
    TileInfo(SharedContext* sContext, SheetInfo& sInfo, const std::string& textureId = "",
             const sf::Vector2u& tilesheetLocation = sf::Vector2u(0, 0))
        : m_context(sContext)
        , m_isCollidable(false)
        , m_isDestructible(false)
        , m_isBase(false)
    {
        TextureLoader* texLoader = sContext->m_textureLoader;
        
        if (textureId == "" || !texLoader->AllocateResource(textureId))
            return;

        m_textureId = textureId;
        m_sprite.setTexture(*texLoader->GetResource(textureId));
        
        sf::IntRect tileBox(tilesheetLocation.x, tilesheetLocation.y,
                            sInfo.m_tileSize.x, sInfo.m_tileSize.y);
        m_sprite.setTextureRect(tileBox);
    }

    ~TileInfo() {
        if (m_textureId == "")
            return;

        m_context->m_textureLoader->ReleaseResource(m_textureId);
    }

    sf::Sprite m_sprite;
    std::string m_textureId;
    bool m_isCollidable;
    bool m_isDestructible;
    bool m_isBase;
    SharedContext* m_context;
};

struct Tile {
    unsigned int m_id; //Not really needed, but simplifies getting a specific tile via it's position.
    TileInfo* m_info;
    sf::Vector2u m_position;
};

//tileName - tile info instance
using TileSet = std::unordered_map<std::string, TileInfo*>;
//id - tile
using TileMap = std::unordered_map<unsigned int, Tile*>;

class GameMap
{
public:
    GameMap(SharedContext* context);
    ~GameMap();

    Tile* GetTileByLocation(sf::Vector2f location);
    SheetInfo* GetSheetInfo();
    const sf::Vector2u& GetMapSize() const;
    const sf::Vector2f& GetPlayerStartLocation() const;
    void LoadMap(const std::string& mapName);
    void LoadNext();
    void Update(float deltaTime);
    void Render();

private:
    SharedContext* m_sharedContext;
    TileSet m_tileSet;
    TileMap m_tileMap;
    SheetInfo m_sheetInfo;
    sf::Vector2u m_mapSize;
    sf::Vector2f m_playerStartLoc;
    sf::Sprite m_background;
    std::string m_backgroundSpriteID;
    unsigned int m_tileCount;
    unsigned int m_tileSetCount;
    std::string m_nextMapName;
    bool m_loadNextMap;

    void LoadTileSet(const std::string& path);
    void PurgeMap();
    void PurgeTileSet();
};

