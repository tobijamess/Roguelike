#include "enemy.h"
#include "utility.h"

void Orc::Initialize() {
	spriteSize = sf::Vector2f(64.f, 64.f);
	enemyScaleFactor = sf::Vector2f(2.f, 2.f);
	hitboxScaleFactor = 1.f;
	detectionRadius = 200.f;
	attackRadius = 400.f;
	health = 100;
	speed = 2.5f;
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
	/*if (IsPlayerInRange(playerPos, detectionRadius)) {
		if (!IsPlayerInRange(playerPos, attackRadius)) {
			sf::Vector2f direction = playerPos - sprite.getPosition();
			direction = Utility::NormalizeVector(direction);
			sprite.move(direction * speed * dt);
			hitbox.move(direction * speed * dt);
		}
	}*/
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
	attackRadius = 200.f;
	health = 50;
	speed = 4.f;
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

}

void Goblin::Draw(sf::RenderWindow& window) {
	window.draw(sprite);
	window.draw(hitbox);
	window.draw(attackCircle);
	window.draw(detectionCircle);
}

//bool Enemy::IsPlayerInRange(const sf::Vector2f& playerPos, float radius) {
//	sf::Vector2f direction = playerPos - sprite.getPosition();
//	float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
//	return distance <= radius;
//}