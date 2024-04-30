#include "EntityManager.h"
#include "SharedContext.h"

EntityManager::EntityManager(SharedContext* sContext, unsigned int maxEntities)
    : m_sContext(sContext)
    , m_maxEntities(maxEntities)
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

void EntityManager::Add(const EntityType& type)
{
    auto itr = m_entityFactory.find(type);

    if (itr == m_entityFactory.end())
        return;

    EntityBase* entity = itr->second();
    m_entities.emplace(entity->GetID(), entity);
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
    m_entityCounter = 0;
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

    for (auto itr = m_entities.begin(); std::next(itr) != m_entities.end(); ++itr)
    {
        for (auto itr2 = std::next(itr); itr2 != m_entities.end(); ++itr2)
        {
            //if (itr->first == itr2->first)
            //    continue;

            //if (itr->second->m_AABB.intersects(itr2->second->m_AABB)) {
            //    itr->second->OnEntityCollision(itr2->second, false);
            //    itr2->second->OnEntityCollision(itr->second, false);
            //}
            //EntityType t1 = itr->second->GetType();
            //EntityType t2 = itr2->second->GetType();
            //if (t1 == EntityType::Player || t1 == EntityType::Enemy) {
            //    Character* c1 = (Character*)itr->second;
            //    if (c1->m_attackAABB.intersects(itr2->second->m_AABB)) {
            //        c1->OnEntityCollision(itr2->second, true);
            //    }
            //}
            //if (t2 == EntityType::Player || t2 == EntityType::Enemy) {
            //    Character* c2 = (Character*)itr2->second;
            //    if (c2->m_attackAABB.intersects(itr->second->m_AABB)) {
            //        c2->OnEntityCollision(itr->second, true);
            //    }
            //}
        }
    }
}
