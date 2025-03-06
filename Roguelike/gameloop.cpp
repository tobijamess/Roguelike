#include "gameloop.h"
#include "toroidalgeneration.h"

Game::Game()
	: window(sf::VideoMode(1280, 720), "Roguelike"),
	player(),
	enemyManager(player),
	projectileManager(player)
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

	// update entities
	player.Update(dt);
	enemyManager.UpdateEnemies(dt);
	projectileManager.UpdateProjectiles(window, dt);

	// enemy spawning
	if (enemyManager.GetEnemies().size() < enemyManager.GetEnemyCap()) {
		enemyManager.SpawnRandomEnemy();
	}

	// player->enemy collision
	for (const auto& enemy : enemyManager.GetEnemies()) {
		if (Collision::PlayerEnemyCollision(player, *enemy, dt,
			player.GetMovingStatus())) {
		}
	}

	// player->tile collision
	Collision::HandleTileCollisionsMTV(player.GetSprite(), player.GetHitbox(),
		player.ConstGetSpeed(), dt, map, baseTileSize, player.GetMovingStatus());

	// enemy->tile collision
	for (const auto& enemy : enemyManager.GetEnemies()) {
		Collision::HandleTileCollisionsMTV(enemy->GetSprite(), enemy->GetHitbox(),
			enemy->ConstGetSpeed(), dt, map, baseTileSize, enemy->GetMovingStatus());
	}

	// projectile->entity collision
	for (const auto& proj : projectileManager.GetProjectiles()) {

		if (!proj->IsFired())
			continue;

		if (proj->GetOwner() == ProjectileOwner::PLAYER) {
			// skip if projectile owner is player to prevent friendly fire
			if (Collision::CheckCircleCollision(proj->ConstGetHitbox(),
				player.ConstGetHitbox())) {
				continue;
			}
			for (auto& enemy : enemyManager.GetEnemies()) {
				if (Collision::CheckCircleCollision(proj->ConstGetHitbox(),
					enemy->ConstGetHitbox())) {
					enemy->TakeDamage(proj->ConstGetDamage());
					proj->SetFired(false);
				}
			}
		}
		else if (proj->GetOwner() == ProjectileOwner::ENEMY) {
			// skip if projectile owner is enemy to prevent friendly fire
			for (auto& enemy : enemyManager.GetEnemies()) {
				if (Collision::CheckCircleCollision(proj->ConstGetHitbox(),
					enemy->ConstGetHitbox())) {
					continue;
				}
				else if (Collision::CheckCircleCollision(proj->ConstGetHitbox(),
					player.ConstGetHitbox())) {
					player.TakeDamage(proj->ConstGetDamage());
					proj->SetFired(false);
				}
			}
		}

		// clear enemies with health <= 0
		enemyManager.RemoveDeadEnemies();

		// projectile->tile collision
		Collision::HandleTileCollisionsMTV(proj->GetSprite(), proj->GetHitbox(),
			proj->ConstGetSpeed(), dt, map, baseTileSize, proj->GetMovingStatus(),
			[&]() {
				proj->SetFired(false);
			}
		);
	}

	// player->map wrapping
	sf::Vector2f newPlayerPos = Toroidal::WrapPosition(player.GetSprite().getPosition(), map, baseTileSize);
	player.GetSprite().setPosition(newPlayerPos);
	player.GetHitbox().setPosition(newPlayerPos);

	// enemy->map wrapping
	for (auto& enemy : enemyManager.GetEnemies()) {
		Toroidal::WrapEntity(enemy->GetSprite(), enemy->GetHitbox(), map, baseTileSize);
	}

	// projectile->map wrapping
	for (auto& proj : projectileManager.GetProjectiles()) {
		Toroidal::WrapEntity(proj->GetSprite(), proj->GetHitbox(), map, baseTileSize);
	}

	window.clear();
	DrawMap(window);
	player.Draw(window);
	enemyManager.DrawEnemies(window);
	projectileManager.DrawProjectiles(window);
	window.display();
}