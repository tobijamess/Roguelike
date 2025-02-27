#include "enemymanager.h"

EnemyManager::EnemyManager(Player& plyr)
	: player(plyr), orc(plyr), goblin(plyr)
{}

void EnemyManager::InitializeEnemies() {
	orc.Initialize();
	goblin.Initialize();
}

void EnemyManager::LoadEnemies() {
	orc.Load();
	goblin.Load();
}

void EnemyManager::UpdateEnemies(float dt) {
    for (auto& enemy : enemies) {
        enemy->Update(dt);
    }
}

void EnemyManager::DrawEnemies(sf::RenderWindow& window) {
    for (auto& enemy : enemies) {
        enemy->Draw(window);
    }
}

void EnemyManager::SpawnRandomEnemy() {
    std::unique_ptr<Enemy> enemy;
    // randomly choose enemy type
    if (rand() % 2 == 0) {
        enemy = std::make_unique<Orc>(player);
    }
    else {
        enemy = std::make_unique<Goblin>(player);
    }

    enemy->Initialize();
    enemy->Load();

    // generate random position values 
    // MAKE RELATIVE TO TILEMAP WHEN IMPLEMENTED
    float x = static_cast<float>(rand() % 1280);
    float y = static_cast<float>(rand() % 720);
    enemy->SetPosition(sf::Vector2f(x, y));

    enemies.push_back(std::move(enemy));
}