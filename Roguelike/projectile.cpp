#include "projectile.h"

void Fireball::Initialize() {
	spriteSize = sf::Vector2f(32.f, 32.f);
	projScaleFactor = sf::Vector2f(0.5f, 0.5f);
	hitboxScaleFactor = 0.5f;
	speed = 600.f;
}

void Fireball::Load() {
	if (!texture.loadFromFile("assets/projectile/textures/fireball.png"))
		return;
	std::cout << "Fireball texture loaded successfully!\n";

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(xSpriteIndex * spriteSize.x,
		ySpriteIndex * spriteSize.y,
		spriteSize.x, spriteSize.y));
	sprite.setPosition(player.ConstGetSprite().getPosition());
	sprite.setScale(projScaleFactor);
	sprite.setOrigin(spriteSize.x / 2.f, spriteSize.y / 2.f);

	SetupComponents();
}

void Fireball::Update(sf::Vector2f dir, float rot, float dt) {
	direction = dir;
	rotation = rot;
	sprite.setRotation(rotation);
	sprite.setPosition(sprite.getPosition() + direction * speed * dt);
	hitbox.setPosition(sprite.getPosition());
}

void Fireball::Draw(sf::RenderWindow& window) {
	window.draw(sprite);
	window.draw(hitbox);
}

void Arrow::Initialize() {
	spriteSize = sf::Vector2f(32.f, 32.f);
	projScaleFactor = sf::Vector2f(0.5f, 0.5f);
	hitboxScaleFactor = 0.5f;
	speed = 750.f;
}

void Arrow::Load() {
	if (!texture.loadFromFile("assets/projectile/textures/arrow.png"))
		return;
	std::cout << "Arrow texture loaded successfully!\n";

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(xSpriteIndex * spriteSize.x,
		ySpriteIndex * spriteSize.y,
		spriteSize.x, spriteSize.y));
	sprite.setPosition(player.ConstGetSprite().getPosition());
	sprite.setScale(projScaleFactor);
	sprite.setOrigin(spriteSize.x, spriteSize.y);

	SetupComponents();
}

void Arrow::Update(sf::Vector2f dir, float rot, float dt) {
	direction = dir;
	rotation = rot;
	sprite.setRotation(rotation);
	sprite.setPosition(sprite.getPosition() + direction * speed * dt);
	hitbox.setPosition(sprite.getPosition());
}

void Arrow::Draw(sf::RenderWindow& window) {
	window.draw(sprite);
	window.draw(hitbox);
}