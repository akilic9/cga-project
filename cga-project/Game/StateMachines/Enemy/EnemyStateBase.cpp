#include "EnemyStateBase.h"

EnemyStateBase::EnemyStateBase(const std::string& name, const int& id, EnemyStateManager* stateManager)
    : StateBase(name, id)
    , m_stateManager(stateManager) {}

EnemyStateBase::~EnemyStateBase() {}

void EnemyStateBase::OnCreate() {}

void EnemyStateBase::OnEnter() {}

void EnemyStateBase::Update(float deltaTime) {}

void EnemyStateBase::Render() {}

void EnemyStateBase::OnExit() {}

void EnemyStateBase::OnDelete() {}
