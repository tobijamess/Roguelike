#include "gameloop.h"
#include "initialization.h"

Game::Game()
	: window(sf::VideoMode(1280, 720), "Roguelike")
{
	view.setSize(window.getSize().x, window.getSize().y);
	window.setView(view);
	
	// load and initialize class instances
	enemyManager.InitializeEnemies();
	enemyManager.LoadEnemies();
	player.Initialize();
	player.Load();
}

void Game::Run() {
	while (window.isOpen()) {
		dt = clock.restart().asSeconds();
		GameLoop(dt);
	}
}

void Game::GameLoop(float dt) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
	}

	enemyManager.UpdateEnemies(dt);
	player.Update(dt);

	window.clear();
	enemyManager.DrawEnemies(window);
	player.Draw(window);
	window.display();

}