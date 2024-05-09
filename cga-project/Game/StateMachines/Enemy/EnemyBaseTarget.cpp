#include "EnemyBaseTarget.h"
#include "EnemyStateManager.h"

EnemyBaseTarget::EnemyBaseTarget(const std::string& name, const int& id, EnemyStateManager* stateManager)
    : EnemyStateBase(name, id, stateManager) {}

EnemyBaseTarget::~EnemyBaseTarget() {}

void EnemyBaseTarget::OnCreate() {}

void EnemyBaseTarget::OnEnter() {}

void EnemyBaseTarget::Update(float deltaTime) {}

void EnemyBaseTarget::Render() {}

void EnemyBaseTarget::OnExit() {}

void EnemyBaseTarget::OnDelete() {}
