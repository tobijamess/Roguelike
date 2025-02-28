#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemymanager.h"
#include "player.h"
#include "collision.h"
#include "map.h"

class Game {
private:
	Player player;
	EnemyManager enemyManager;
	
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
};
#endif