#include "Scene.h"
#include "SceneManager.h"

Scene::Scene(const std::string& name, const int& id, SceneManager* sceneManager)
    : StateBase(name, id, sceneManager)
    , m_sceneManager(sceneManager) {}

Scene::~Scene() {}

void Scene::OnCreate() {}

void Scene::OnEnter() {}

void Scene::Update(float deltaTime) {}

void Scene::Render() {}

void Scene::OnExit() {}

void Scene::OnDelete() {}
