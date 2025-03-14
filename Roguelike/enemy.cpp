#include "enemy.h"
#include "utility.h"

void Orc::Initialize() {
	spriteSize = sf::Vector2f(64.f, 64.f);
	enemyScaleFactor = sf::Vector2f(1.f, 1.f);
	hitboxScaleFactor = 0.25f;
	detectionRadius = 10000.f;
	attackRadius = 50.f;
	health = 100;
	speed = 200.f;
}

void Orc::Load() {
	if (!texture.loadFromFile("assets/enemy/textures/orcspritesheet.png")) 
		return;
	std::cout << "Orc texture loaded successfully!\n";

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(xSpriteIndex * spriteSize.x,
		ySpriteIndex * spriteSize.y,
		spriteSize.x, spriteSize.y));
	sprite.setScale(enemyScaleFactor);
	sprite.setOrigin(spriteSize.x / 2.f, spriteSize.y / 2.f);

	SetupComponents();
}
      
void Orc::Update(float dt) {
	detectionCircle.setPosition(sprite.getPosition());
	attackCircle.setPosition(sprite.getPosition());
	sf::Vector2f playerPos = player.ConstGetSprite().getPosition();
	sf::Vector2f enemyPos = sprite.getPosition();
	if (Utility::IsPlayerInRange(playerPos, enemyPos, detectionRadius)) {
		if (!Utility::IsPlayerInRange(playerPos, enemyPos, attackRadius)) {
			sf::Vector2f direction = playerPos - enemyPos;
			direction = Utility::NormalizeVector(direction);
			sprite.move(direction * speed * dt);
			hitbox.move(direction * speed * dt);
		}
	}
}

void Orc::Draw(sf::RenderWindow& window) {
	window.draw(sprite);
	window.draw(hitbox);
	window.draw(attackCircle);
	window.draw(detectionCircle);
}

void Goblin::Initialize() {
	spriteSize = sf::Vector2f(64.f, 64.f);
	enemyScaleFactor = sf::Vector2f(1.f, 1.f);
	hitboxScaleFactor = 0.25f;
	detectionRadius = 10000.f;
	attackRadius = 50.f;
	health = 50;
	speed = 225.f;
}

void Goblin::Load() {
	if (!texture.loadFromFile("assets/enemy/textures/goblinspritesheet.png"))
		return;
	std::cout << "Goblin texture loaded successfully!\n";

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(xSpriteIndex * spriteSize.x,
		ySpriteIndex * spriteSize.y,
		spriteSize.x, spriteSize.y));
	sprite.setScale(enemyScaleFactor);
	sprite.setOrigin(spriteSize.x / 2.f, spriteSize.y / 2.f);

	SetupComponents();
}

void Goblin::Update(float dt) {
	detectionCircle.setPosition(sprite.getPosition());
	attackCircle.setPosition(sprite.getPosition());
	sf::Vector2f playerPos = player.ConstGetSprite().getPosition();
	sf::Vector2f enemyPos = sprite.getPosition();
	if (Utility::IsPlayerInRange(playerPos, enemyPos, detectionRadius)) {
		if (!Utility::IsPlayerInRange(playerPos, enemyPos, attackRadius)) {
			sf::Vector2f direction = playerPos - enemyPos;
			direction = Utility::NormalizeVector(direction);
			sprite.move(direction * speed * dt);
			hitbox.move(direction * speed * dt);
		}
		isMoving = true;
	}
}

void Goblin::Draw(sf::RenderWindow& window) {
	window.draw(sprite);
	window.draw(hitbox);
	window.draw(attackCircle);
	window.draw(detectionCircle);
}