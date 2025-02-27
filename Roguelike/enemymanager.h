#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemy.h"

class EnemyManager {
private:
	const int enemyCap = 100;
protected:
	std::vector<std::unique_ptr<Enemy>> enemies;
	Orc orc;
	Goblin goblin;
public:
	EnemyManager();
	void InitializeEnemies();
	void LoadEnemies();
	void UpdateEnemies(float dt);
	void DrawEnemies(sf::RenderWindow& window);
};
#endif