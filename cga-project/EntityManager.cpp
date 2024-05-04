#include "EntityManager.h"
#include "SharedContext.h"

EntityManager::EntityManager(SharedContext* sContext, unsigned int maxEntities)
    : m_sContext(sContext)
    , m_maxEntities(maxEntities)
    , m_entityCount(0)
{
    //RegisterEntity<Player>(EntityType::Player);
}

EntityManager::~EntityManager()
{
    Purge();
}

EntityBase* EntityManager::Find(unsigned int id)
{
    auto itr = m_entities.find(id);
    return itr == m_entities.end() ? nullptr : itr->second;
}

EntityBase* EntityManager::Find(const std::string& name)
{
    for (auto& itr : m_entities)
        if (itr.second->GetName() == name)
            return itr.second;

    return nullptr;
}

void EntityManager::Add(const EntityType& type, const std::string name)
{
    auto itr = m_entityFactory.find(type);

    if (itr == m_entityFactory.end())
        return;

    EntityBase* entity = itr->second();
    entity->SetID(m_entityCount);
    entity->SetName(name);
    m_entities.emplace(m_entityCount, entity);
    ++m_entityCount;
}

void EntityManager::QueueForRemoval(unsigned int id)
{
    m_removalQueue.push_back(id);
}

void EntityManager::Update(float deltaTime)
{
    for (auto& entity : m_entities)
        entity.second->Update(deltaTime);

    EntityCollisionCheck();
    ProcessRemovals();
}

void EntityManager::Render()
{
    sf::RenderWindow* window = m_sContext->m_window->GetRenderWindow();

    for (auto& itr : m_entities)
        itr.second->Render(window);
}

void EntityManager::Purge()
{
    for (auto& itr : m_entities)
        delete itr.second;

    m_entities.clear();
    m_entityCount = 0;
}

void EntityManager::ProcessRemovals()
{
    while (m_removalQueue.begin() != m_removalQueue.end()) {
        unsigned int id = m_removalQueue.back();
        auto itr = m_entities.find(id);
        if (itr != m_entities.end()) {
            delete itr->second;
            m_entities.erase(itr);
        }
        m_removalQueue.pop_back();
    }
}

void EntityManager::EntityCollisionCheck()
{
    if (m_entities.empty())
        return;

    for (auto entity = m_entities.begin(); std::next(entity) != m_entities.end(); ++entity)
    {
        for (auto nextEntity = std::next(entity); nextEntity != m_entities.end(); ++nextEntity)
        {
            if (entity->first == nextEntity->first)
                continue;

            if (entity->second->GetBoundingBox().intersects(nextEntity->second->GetBoundingBox())) {
                entity->second->OnEntityCollision(nextEntity->second);
                nextEntity->second->OnEntityCollision(entity->second);
            }
        }
    }
}
