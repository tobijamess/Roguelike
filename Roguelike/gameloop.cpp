#include "gameloop.h"

Game::Game()
	: window(sf::VideoMode(1280, 720), "Roguelike"),
	player(),
	enemyManager(player)
{
	view.setSize(window.getSize().x, window.getSize().y);
	window.setView(view);
	
	// load and initialize class instances
	player.Initialize();
	player.Load();
	enemyManager.LoadEnemies();
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

	if (enemyManager.GetEnemies().size() < enemyManager.GetEnemyCap()) {
		enemyManager.SpawnRandomEnemy();
	}

	for (const auto& enemy : enemyManager.GetEnemies()) {
		if (Collision::PlayerEnemyCollision(player, *enemy, dt,
			player.GetMovingStatus())) {
			std::cout << "Collision with Enemy!\n";
		}
	}
	player.Update(dt);
	enemyManager.UpdateEnemies(dt);
	
	window.clear();
	player.Draw(window);
	enemyManager.DrawEnemies(window);
	window.display();
}