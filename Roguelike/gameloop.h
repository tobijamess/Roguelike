#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "enemymanager.h"
#include "projectilemanager.h"
#include "playerview.h"
#include "collision.h"
#include "map.h"

class Game {
private:
	Player player;
	EnemyManager enemyManager;
	ProjectileManager projectileManager;
	
	sf::RenderWindow window;
	sf::View view;
	sf::Clock clock;
	float dt;

	Map map;
	sf::Texture tileAtlas;
	int baseTileSize = 16;

	void DrawMap(sf::RenderWindow& window);
protected:

public:
	Game();
	void Run();
	void GameLoop(float dt);
	const sf::RenderWindow& ConstGetWindow() const {
		return window;
	}
};
#endif