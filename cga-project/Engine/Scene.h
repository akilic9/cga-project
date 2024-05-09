#pragma once
#include "StateBase.h"

class SceneManager;

class Scene : public StateBase
{
public:
    Scene(const std::string& name, const int& id, SceneManager* sceneManager)
        : StateBase(name, id)
        , m_sceneManager(sceneManager) {}
    ~Scene() {}

    virtual void OnCreate() = 0;
    virtual void OnEnter() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual void OnExit() = 0;
    virtual void OnDelete() = 0;

protected:
    SceneManager* m_sceneManager;
};

