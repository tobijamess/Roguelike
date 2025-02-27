#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemymanager.h"
#include "player.h"
#include "collision.h"

class Game {
private:
	Player player;
	EnemyManager enemyManager;
	
	sf::RenderWindow window;
	sf::View view;
	sf::Clock clock;
	float dt;
protected:

public:
	Game();
	void Run();
	void GameLoop(float dt);
};
#endif