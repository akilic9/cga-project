#pragma once
#include <functional>
#include "EntityBase.h"

using EntityContainer = std::unordered_map<unsigned int, EntityBase*>;
using EntityFactory = std::unordered_map<EntityType, std::function<EntityBase* (void)>>;

struct SharedContext;

class EntityManager
{
public:
    EntityManager(SharedContext* sContext, unsigned int maxEntities);
    ~EntityManager();

    EntityBase* Find(unsigned int& id);
    EntityBase* Find(const std::string& name);

    void Add(const EntityType& type, const std::string& name);
    void QueueForRemoval(unsigned int& id);

    void Update(float deltaTime);
    void Render();
    void Purge();

    SharedContext* GetSharedContext() const { return m_sContext; }

private:
    EntityContainer m_entities;
    EntityFactory m_entityFactory;
    SharedContext* m_sContext;
    unsigned int m_entityCount;
    unsigned int m_maxEntities;
    std::vector<unsigned int> m_removalQueue;

    template<class T>void RegisterEntity(const EntityType& type) {
        m_entityFactory[type] = [this]() -> EntityBase*
            { return new T(this); };
    }
    void ProcessRemovals();
    void EntityCollisionCheck();
};

