#include "enemymanager.h"

EnemyManager::EnemyManager() {}

void EnemyManager::InitializeEnemies() {
	orc.Initialize();
	goblin.Initialize();
}

void EnemyManager::LoadEnemies() {
	orc.Load();
	goblin.Load();
}

void EnemyManager::UpdateEnemies(float dt) {
	orc.Update(dt);
	goblin.Update(dt);
}

void EnemyManager::DrawEnemies(sf::RenderWindow& window) {
	orc.Draw(window);
	goblin.Draw(window);
}