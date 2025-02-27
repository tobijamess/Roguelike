#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemy.h"
#include "player.h"

class EnemyManager {
private:
	Player& player;
	const int enemyCap = 1;
protected:
	std::vector<std::unique_ptr<Enemy>> enemies;
	Orc orc;
	Goblin goblin;
public:
	EnemyManager(Player& plyr);
	void InitializeEnemies();
	void LoadEnemies();
	void UpdateEnemies(float dt);
	void DrawEnemies(sf::RenderWindow& window);
	void SpawnRandomEnemy();
	// getter for collision detection loop
	const std::vector<std::unique_ptr<Enemy>>& GetEnemies() const {
		return enemies;
	}
	const int GetEnemyCap() const {
		return enemyCap;
	}
};
#endif