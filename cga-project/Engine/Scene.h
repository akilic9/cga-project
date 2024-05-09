#pragma once
#include "StateBase.h"

class SceneManager;

class Scene : public StateBase
{
public:
    Scene(const std::string& name, const int& id, SceneManager* sceneManager);
    ~Scene();

    virtual void OnCreate();
    virtual void OnEnter();
    virtual void Update(float deltaTime);
    virtual void Render();
    virtual void OnExit();
    virtual void OnDelete();

protected:
    SceneManager* m_sceneManager;
};

