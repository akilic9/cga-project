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

    EntityBase* Find(unsigned int id);
    EntityBase* Find(const std::string& name);

    void Add(const EntityType& type);
    void QueueForRemoval(unsigned int id);

    void Update(float deltaTime);
    void Render();
    void Purge();

    SharedContext* GetSharedContext() { return m_sContext; }

private:
    EntityContainer m_entities;
    EntityFactory m_entityFactory;
    SharedContext* m_sContext;
    unsigned int m_entityCounter = 0;
    unsigned int m_maxEntities;
    std::vector<unsigned int> m_removalQueue;


    template<class T>void RegisterEntity(const EntityType& type, std::string name) {
        unsigned int id = m_entityCounter++;
        m_entityFactory[type] = [this, name, id]() -> EntityBase*
            {
                return new T(this, name, id);
            };
    }
    void ProcessRemovals();
    void EntityCollisionCheck();
};

