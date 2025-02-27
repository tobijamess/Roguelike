#include "player.h"
#include "utility.h"
#include "collision.h"

Player::Player()
    : health(200),
    speed(300.f),
    hitboxScaleFactor(1.f)
{}

void Player::Initialize() {
    spriteSize = sf::Vector2f(64.f, 64.f);
    playerScaleFactor = sf::Vector2f(2.f, 2.f);
}

void Player::Load() {
	if (!texture.loadFromFile("assets/player/textures/playerspritesheet.png"))
		return;
	std::cout << "Player texture loaded successfully!\n";

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(xSpriteIndex * spriteSize.x,
        ySpriteIndex * spriteSize.y, spriteSize.x, spriteSize.y));
	sprite.setPosition(400, 400);
    sprite.setScale(playerScaleFactor);
    sprite.setOrigin(spriteSize.x / 2.f, spriteSize.y / 2.f);

    float scaledWidth = spriteSize.x * hitboxScaleFactor;
    float scaledHeight = spriteSize.y * hitboxScaleFactor;
    hitboxRadius = std::max(scaledWidth, scaledHeight) / 2.f;

    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(1.f);
    hitbox.setRadius(hitboxRadius);
    hitbox.setOrigin(hitboxRadius, hitboxRadius);
    hitbox.setPosition(sprite.getPosition());
}

void Player::Update(float dt) {
	sf::Vector2f movement(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.y -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movement.x -= speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += speed;
    }
    if (movement.x != 0.0f || movement.y != 0.0f) {
        // normalize the movement vector to prevent extra speed on diagonals
        movement = Utility::NormalizeVector(movement);
    }

    bool isMoving = (sf::Keyboard::isKeyPressed(sf::Keyboard::W) 
        || sf::Keyboard::isKeyPressed(sf::Keyboard::A) 
        || sf::Keyboard::isKeyPressed(sf::Keyboard::S) 
        || sf::Keyboard::isKeyPressed(sf::Keyboard::D));

    sprite.move(movement * speed * dt);
    hitbox.move(movement * speed * dt);
}

void Player::Draw(sf::RenderWindow& window) {
	window.draw(sprite);
    window.draw(hitbox);
}

void Player::Move(const sf::Vector2f& offset) {
    // move sprite and hitbox based on collision offset
    sprite.setPosition(sprite.getPosition() + offset);
    hitbox.setPosition(sprite.getPosition());
}