#include "EnemyAttack.h"
#include "EnemyStateManager.h"
#include "../../Enemy.h"

EnemyAttack::EnemyAttack(const std::string& name, const int& id, EnemyStateManager* stateManager, Enemy* enemy)
    : EnemyStateBase(name, id, stateManager, enemy) {}

EnemyAttack::~EnemyAttack() {}

void EnemyAttack::OnCreate() {}

void EnemyAttack::OnEnter() {}

void EnemyAttack::Update(float deltaTime) {}

void EnemyAttack::Render() {}

void EnemyAttack::OnExit() {}

void EnemyAttack::OnDelete() {}
