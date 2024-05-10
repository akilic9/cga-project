#pragma once
#include <unordered_map>
#include <SFML/Graphics/Sprite.hpp>
#include "SharedContext.h"

struct SheetInfo {
    sf::Vector2u m_sheetSize;
    sf::Vector2u m_defaultTileSize;
};

struct TileInfo {
    TileInfo(SharedContext* sContext, SheetInfo& sInfo, const std::string& textureId = "",
             const sf::Vector2u& tilesheetLocation = sf::Vector2u(0, 0))
        : m_context(sContext)
        , m_isCollidable(false)
        , m_isDestructible(false)
        , m_isBase(false)
        , m_tilePosition(0.f, 0.f)
    {
        TextureLoader* texLoader = sContext->m_textureLoader;
        
        if (textureId == "" || !texLoader->AllocateResource(textureId))
            return;

        m_textureId = textureId;
        m_sprite.setTexture(*texLoader->GetResource(textureId));
        
        sf::IntRect tileBox(tilesheetLocation.x, tilesheetLocation.y,
                            sInfo.m_defaultTileSize.x, sInfo.m_defaultTileSize.y);
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
    sf::Vector2f m_tilePosition;
};

struct Tile {
    unsigned int m_id;
    TileInfo* m_info;
    sf::Vector2u m_position;
    sf::Vector2f m_centerCoord;
};

//tileName - tile info object
using TileSet = std::unordered_map<std::string, TileInfo*>;
//id - tile object
using TileMap = std::unordered_map<unsigned int, Tile*>;

class GameMap
{
public:
    GameMap(SharedContext* context);
    ~GameMap();

    Tile* GetTileByLocation(sf::Vector2f location) const;
    SheetInfo* GetSheetInfo();
    sf::Vector2u& GetMapSize();
    sf::Vector2f& GetPlayerStartLocation();
    sf::Vector2f& GetBaseLocation();
    std::vector<sf::Vector2f>& GetEnemyStartLocs();
    void LoadMap(const std::string& mapName);
    void LoadNext();
    void Update(float deltaTime);
    void Render();

private:
    SharedContext* m_sharedContext;
    TileSet m_tileSet;
    TileMap m_tileMap;
    std::vector<sf::Vector2f> m_movableTiles;
    SheetInfo m_sheetInfo;
    sf::Vector2u m_mapSize;
    sf::Vector2f m_playerSpawnLoc;
    sf::Vector2f m_baseLoc;
    std::vector<sf::Vector2f> m_enemySpawnLocs;
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

