#include "gameloop.h"

Game::Game()
	: window(sf::VideoMode(1280, 720), "Roguelike"),
	player(),
	enemyManager(player)
{	
	// load and initialize class instances
	player.Initialize();
	player.Load();
	enemyManager.LoadEnemies();

	if (!tileAtlas.loadFromFile("assets/map/tilemap16.png")) {
		std::cerr << "Failed to load Tile Atlas.\n";
	}

	if (!LoadMap("assets/map/test.json", tileAtlas, baseTileSize, map)) {
		std::cerr << "Failed to load Map.\n";
	}
}

void Game::DrawMap(sf::RenderWindow& window) {
	// iterate over each layer in the map
	for (const auto& layer : map.layers) {
		// loop through each tile in the layer
		for (int y = 0; y < layer.height; ++y) {
			for (int x = 0; x < layer.width; ++x) {
				const Tile& tile = layer.tiles[y][x];
				// draw the tile sprite if it is valid
				if (tile.index >= 0) {
					window.draw(tile.sprite);
				}
				// draw a collision overlay for collidable tiles
				if (layer.collisionGrid[y][x]) {
					sf::RectangleShape collisionRect(sf::Vector2f(baseTileSize,
						baseTileSize));
					collisionRect.setPosition(static_cast<float>(x * baseTileSize),
						static_cast<float>(y * baseTileSize));
					collisionRect.setFillColor(sf::Color(255, 0, 0, 100));
					window.draw(collisionRect);
				}
			}
		}
	}
}

void Game::Run() {
	while (window.isOpen()) {
		dt = clock.restart().asSeconds();
		GameLoop(dt);
	}
}

void Game::GameLoop(float dt) {
	PlayerView::SetUpPlayerView(player, window);
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

	Collision::HandleTileCollisionsMTV(player.GetSprite(), player.GetHitbox(),
		player.ConstGetSpeed(), dt, map, baseTileSize, player.GetMovingStatus());

	for (const auto& enemy : enemyManager.GetEnemies()) {
		Collision::HandleTileCollisionsMTV(enemy->GetSprite(), enemy->GetHitbox(),
			enemy->ConstGetSpeed(), dt, map, baseTileSize, enemy->GetMovingStatus());
	}
	
	window.clear();

	DrawMap(window);

	player.Draw(window);
	enemyManager.DrawEnemies(window);

	

	window.display();
}

