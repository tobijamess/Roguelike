#include "enemy.h"
#include "utility.h"

void Orc::Initialize() {
	spriteSize = sf::Vector2f(64.f, 64.f);
	enemyScaleFactor = sf::Vector2f(2.f, 2.f);
	hitboxScaleFactor = 1.f;
	detectionRadius = 300.f;
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
	sprite.setPosition(700, 600);
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
	enemyScaleFactor = sf::Vector2f(2.f, 2.f);
	hitboxScaleFactor = 1.f;
	detectionRadius = 100.f;
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
	sprite.setPosition(300, 200);
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
	}
}

void Goblin::Draw(sf::RenderWindow& window) {
	window.draw(sprite);
	window.draw(hitbox);
	window.draw(attackCircle);
	window.draw(detectionCircle);
}