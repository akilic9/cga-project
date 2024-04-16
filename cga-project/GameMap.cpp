#include "GameMap.h"

GameMap::GameMap(SharedContext* context)
    : m_sharedContext(context)
    , m_defaultTile(m_sharedContext, m_sheetInfo)
    , m_mapSize(0, 0)
    , m_playerStartLoc(0.f, 0.f)
    , m_tileCount(0)
    , m_tileSetCount(0)
    , m_nextMapName("")
    , m_loadNextMap(false)
{
    m_sharedContext->m_mapManager = this;
    LoadTileSet("TilesetData.cfg");
}

GameMap::~GameMap()
{
    PurgeMap();
    PurgeTileSet();
    m_sharedContext->m_mapManager = nullptr;
}

Tile* GameMap::GetTileByLocation(sf::Vector2u location)
{
    //TODO
    return nullptr;
}

TileInfo* GameMap::GetDefaultTile()
{
    return &m_defaultTile;
}

const sf::Vector2u& GameMap::GetMapSize() const
{
    return m_mapSize;
}

const sf::Vector2f& GameMap::GetPlayerStartLocation() const
{
    return m_playerStartLoc;
}

void GameMap::LoadMap(const std::string& mapName)
{
    std::ifstream mapDataFile;
    mapDataFile.open("Data/Maps/" + mapName);
    if (!mapDataFile.is_open()) {
        std::cerr << "Cannot open tileset config at: " << mapName << std::endl;
        return;
    }

    std::string line;
    while (std::getline(mapDataFile, line)) {
        if (line[0] == '<') //Comment line.
            continue;
        std::stringstream keystream(line);
        std::string type;
        keystream >> type;

        if (type == "TILE") {
            std::string tileType;
            keystream >> tileType;

            auto typeItr = m_tileSet.find(tileType);
            if (typeItr == m_tileSet.end()) {
                std::cerr << "Invalid tile type, could not find in the tile set: " << tileType << std::endl;
                continue;
            }
            sf::Vector2u tilePosition;
            keystream >> tilePosition.x >> tilePosition.y;
            if (tilePosition.x > m_sharedContext->m_window->GetWindowSize().x || tilePosition.x < 0 ||
                tilePosition.y > m_sharedContext->m_window->GetWindowSize().y || tilePosition.y < 0) {
                std::cerr << "Invalid tile position: " << line << std::endl;
                continue;
            }
            Tile* tile = new Tile;
            tile->m_info = typeItr->second;
            std::string tileId = std::to_string(tilePosition.x) + std::to_string(tilePosition.y); //Id will be the row and column.
            tile->m_id = stoi(tileId);
            tile->m_position = sf::Vector2u(tilePosition.x * m_sheetInfo.m_tileSize.x,
                tilePosition.y * m_sheetInfo.m_tileSize.y);

            if (!m_tileMap.emplace(tile->m_id, tile).second) {
                std::cerr << "Overlapping tiles: " << line << std::endl;
                delete tile;
                tile = nullptr;
                continue;
            }
        }
        else if (type == "MAPSIZE")
            keystream >> m_mapSize.x >> m_mapSize.y;
        else if (type == "PLAYERLOCATION")
            keystream >> m_playerStartLoc.x >> m_playerStartLoc.y;
        else if (type == "NEXTMAP")
            keystream >> m_nextMapName;
        else
            std::cerr << "Unknown parameter type: " << line << std::endl;
    }
}

void GameMap::LoadNext()
{
    m_loadNextMap = true;
}

void GameMap::Update(float deltaTime)
{
    if (m_loadNextMap) {
        PurgeMap();
        m_loadNextMap = false;

        if (m_nextMapName != "") {
            LoadMap(m_nextMapName);
            m_nextMapName = "";
        }
    }
}

void GameMap::Render()
{
    sf::RenderWindow* window = m_sharedContext->m_window->GetRenderWindow();

    for (auto &t : m_tileMap) {
        sf::Sprite& sprite = t.second->m_info->m_sprite;
        sprite.setPosition(t.second->m_position.x, t.second->m_position.y);
        window->draw(sprite);
    }
}

void GameMap::LoadTileSet(const std::string& path)
{
    std::ifstream tileSetfile;
    tileSetfile.open("Data/" + path);
    if (!tileSetfile.is_open()) {
        std::cerr << "Cannot open tileset config at: " << path << std::endl;
        return;
    }
    std::string line;
    while (std::getline(tileSetfile, line)) {
        if (line[0] == '<') //Comment line.
            continue;
        std::stringstream keystream(line);
        std::string parameter;
        keystream >> parameter;

        if (parameter == "SheetSize") {
            sf::Vector2u sheetSize;
            keystream >> sheetSize.x >> sheetSize.y;
            m_sheetInfo.m_sheetSize = sheetSize;
        }
        else if (parameter == "TileSize") {
            sf::Vector2u tileSize;
            keystream >> tileSize.x >> tileSize.y;
            m_sheetInfo.m_tileSize = tileSize;
        }
        else if (parameter == "TileType") {
            sf::Vector2u location;
            std::string tileName;
            keystream >> tileName >> location.x >> location.y;
            TileInfo* tile = new TileInfo(m_sharedContext, m_sheetInfo, tileName, location);
            keystream >> tile->m_isCollidable >> tile->m_isDestructible >> tile->m_isBase;
            if (!m_tileSet.emplace(tileName, tile).second) {
                std::cerr << "A tile type was defined twice in tile config: " << tileName << std::endl;
                delete tile;
            }
        }
    }
    tileSetfile.close();
}

void GameMap::PurgeMap()
{
    m_tileCount = 0;
    for (auto& itr : m_tileMap) {
        delete itr.second;
    }
    m_tileMap.clear();
}

void GameMap::PurgeTileSet()
{
    m_tileSetCount = 0;
    for (auto& itr : m_tileSet) {
        delete itr.second;
    }
    m_tileSet.clear();
}