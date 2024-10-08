#include "EntityManager.h"
#include "SharedContext.h"

EntityManager::EntityManager(SharedContext* sContext)
    : m_sContext(sContext)
    , m_entityCount(0)
{
    RegisterEntity<Player>(EntityType::Player);
    RegisterEntity<Enemy>(EntityType::Enemy);
    RegisterEntity<Bullet>(EntityType::Bullet);
    RegisterEntity<PowerUpNuke>(EntityType::PowerUp);
}

EntityManager::~EntityManager()
{
    Purge();
}

EntityBase* EntityManager::Find(unsigned int& id)
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

void EntityManager::Add(const EntityType& type, const std::string& name)
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

void EntityManager::QueueForRemoval(unsigned int& id)
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
    for (auto& itr : m_entities) {
        delete itr.second;
        itr.second = nullptr;

    }

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

            if ((entity->second->GetType() == EntityType::Player || entity->second->GetType() == EntityType::Enemy))
                if (static_cast<Character*>(entity->second)->GetCurrentState() == CharacterState::Dead)
                    continue;

            if ((nextEntity->second->GetType() == EntityType::Player || nextEntity->second->GetType() == EntityType::Enemy))
                if (static_cast<Character*>(nextEntity->second)->GetCurrentState() == CharacterState::Dead)
                    continue;

            if (entity->second->GetType() == EntityType::Bullet)
                if (!static_cast<Bullet*>(entity->second)->GetActive())
                    continue;

            if (nextEntity->second->GetType() == EntityType::Bullet)
                if (!static_cast<Bullet*>(nextEntity->second)->GetActive())
                    continue;

            if (entity->second->GetBoundingBox().intersects(nextEntity->second->GetBoundingBox())) {
                entity->second->OnEntityCollision(nextEntity->second);
                nextEntity->second->OnEntityCollision(entity->second);
            }
        }
    }
}
