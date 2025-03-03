#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"

class Enemy {
protected:
	Player& player;
	sf::Texture texture;				// spritesheet texture
	sf::Sprite sprite;					// enemy sprite
	int xSpriteIndex;					// x index of sprite texture
	int ySpriteIndex;					// y index of sprite texture
	sf::Vector2f spriteSize;			// size of the sprite in px
	sf::Vector2f enemyScaleFactor;		// scale of the sprite

	int health;
	float speed;
	bool isMoving = false;

	float hitboxScaleFactor;			// scale of the hitbox
	sf::CircleShape hitbox;				// hitbox for enemy
	float hitboxRadius;					// radius of hitbox

	float detectionRadius;				// size of detection range
	sf::CircleShape detectionCircle;	// decides if player is detectable
	float attackRadius;					// size of attack range
	sf::CircleShape attackCircle;		// decides if player is in attack range

	void SetupComponents() {
		// Calculate the hitbox radius based on sprite size and scale factor.
		float scaledWidth = spriteSize.x * hitboxScaleFactor;
		float scaledHeight = spriteSize.y * hitboxScaleFactor;
		hitboxRadius = std::max(scaledWidth, scaledHeight) / 2.f;

		// Configure the hitbox.
		hitbox.setFillColor(sf::Color::Transparent);
		hitbox.setOutlineColor(sf::Color::Red);
		hitbox.setOutlineThickness(1.f);
		hitbox.setRadius(hitboxRadius);
		hitbox.setOrigin(hitboxRadius, hitboxRadius);
		hitbox.setPosition(sprite.getPosition());

		// Configure the detection circle.
		detectionCircle.setRadius(detectionRadius);
		detectionCircle.setOrigin(detectionRadius, detectionRadius);
		detectionCircle.setFillColor(sf::Color::Transparent);
		detectionCircle.setOutlineColor(sf::Color::Green);
		detectionCircle.setOutlineThickness(1);
		detectionCircle.setPosition(sprite.getPosition());

		// Configure the attack circle.
		attackCircle.setRadius(attackRadius);
		attackCircle.setOrigin(attackRadius, attackRadius);
		attackCircle.setFillColor(sf::Color::Transparent);
		attackCircle.setOutlineColor(sf::Color::Blue);
		attackCircle.setOutlineThickness(1);
		attackCircle.setPosition(sprite.getPosition());
	}

public:
	// constructor
	Enemy(Player& plyr, sf::Texture txtre, sf::Sprite sprt, int xIndx, int yIndx,
		sf::Vector2f size, sf::Vector2f scale, int hp, float spd, bool moving,
		float htbxScale, sf::CircleShape htbx, float htbxRad, float dtctRad,
		sf::CircleShape dtctCrcl, float atkRad, sf::CircleShape atkCrcl)
		: player(plyr), texture(txtre), sprite(sprt), xSpriteIndex(xIndx),
		ySpriteIndex(yIndx), spriteSize(size), enemyScaleFactor(scale), health(hp),
		speed(spd), isMoving(moving), hitboxScaleFactor(htbxScale), hitbox(htbx),
		hitboxRadius(htbxRad), detectionRadius(dtctRad), detectionCircle(dtctCrcl),
		attackRadius(atkRad), attackCircle(atkCrcl)
	{}

	// destructor
	virtual ~Enemy() = default;

	// override functions
	virtual void Initialize() = 0;
	virtual void Load() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;

	void SetPosition(const sf::Vector2f& pos) {
		sprite.setPosition(pos);
		hitbox.setPosition(pos);
		detectionCircle.setPosition(pos);
		attackCircle.setPosition(pos);
	}

	// getter functions for collision
	const sf::CircleShape& ConstGetHitbox() const {
		return hitbox;
	}
	sf::CircleShape& GetHitbox() {
		return hitbox;
	}
	const sf::Sprite& ConstGetSprite() const {
		return sprite;
	}
	sf::Sprite& GetSprite() {
		return sprite;
	}
	const float& ConstGetSpeed() const {
		return speed;
	}
	const bool& GetMovingStatus() const{
		return isMoving;
	}

};

class Orc : public Enemy {
public:
	// default constructor
	Orc(Player& player)
		: Enemy(player, sf::Texture(), sf::Sprite(), 0, 0, sf::Vector2f(),
			sf::Vector2f(), 0, 0.f, false, 0.f, sf::CircleShape(), 0.f, 0.f,
			sf::CircleShape(), 0.f, sf::CircleShape()) 
	{}

	// derived over-ridden functions
	void Initialize() override;
	void Load() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

class Goblin : public Enemy {
public:
	// default constructor
	Goblin(Player& player)
		: Enemy(player, sf::Texture(), sf::Sprite(), 0, 0, sf::Vector2f(),
			sf::Vector2f(), 0, 0.f, false, 0.f, sf::CircleShape(), 0.f, 0.f,
			sf::CircleShape(), 0.f, sf::CircleShape())
	{}

	// derived over-ridden functions
	void Initialize() override;
	void Load() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

#endif