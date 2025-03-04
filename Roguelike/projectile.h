#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"

enum ProjectileOwner {
	PLAYER,
	ENEMY,
	NONE
};

class Projectile {
protected:
	Player& player;
	sf::Texture texture;
	sf::Sprite sprite;
	int xSpriteIndex;
	int ySpriteIndex;
	sf::Vector2f spriteSize;
	sf::Vector2f projScaleFactor;

	ProjectileOwner owner = ProjectileOwner::NONE;

	int damage;
	float speed;
	bool fired = false;
	bool isMoving = false;
	sf::Vector2f direction = { 0.f, 0.f };
	float rotation = 0.f;

	float hitboxScaleFactor;
	sf::CircleShape hitbox;
	float hitboxRadius;
	
	void SetupComponents() {
		// calculate the hitbox radius based on sprite size and scale factor
		float scaledWidth = spriteSize.x * hitboxScaleFactor;
		float scaledHeight = spriteSize.y * hitboxScaleFactor;
		hitboxRadius = std::max(scaledWidth, scaledHeight) / 2.f;

		// configure the hitbox
		hitbox.setFillColor(sf::Color::Transparent);
		hitbox.setOutlineColor(sf::Color::Red);
		hitbox.setOutlineThickness(1.f);
		hitbox.setRadius(hitboxRadius);
		hitbox.setOrigin(hitboxRadius, hitboxRadius);
		hitbox.setPosition(sprite.getPosition());
	}

public:
	// constructor
	Projectile(Player& plyr, sf::Texture txtre, sf::Sprite sprt, int xIndx, 
		int yIndx, sf::Vector2f size, sf::Vector2f scale, int dmg, float spd, 
		float htbxScale, sf::CircleShape htbx, float htbxRad)
		: player(plyr), texture(txtre), sprite(sprt), xSpriteIndex(xIndx),
		ySpriteIndex(yIndx), spriteSize(size), projScaleFactor(scale), damage(dmg),
		speed(spd), hitboxScaleFactor(htbxScale), hitbox(htbx), hitboxRadius(htbxRad)
	{}

	// destructor
	virtual ~Projectile() = default;

	// override functions
	virtual void Initialize() = 0;
	virtual void Load() = 0;
	virtual void Update(sf::Vector2f direction, float rotation, float dt) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;

	void SetPosition(const sf::Vector2f& pos) {
		sprite.setPosition(pos);
		hitbox.setPosition(pos);
	}

	void SetOwner(ProjectileOwner newOwner) {
		owner = newOwner;
	}
	ProjectileOwner GetOwner() const {
		return owner;
	}

	bool IsFired() const {
		return fired;
	}
	void SetFired(bool state) {
		fired = state;
	}
	void Fire() {
		fired = true;
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
	const int& ConstGetDamage() const {
		return damage;
	}
	const float& ConstGetSpeed() const {
		return speed;
	}
	const bool& GetMovingStatus() const {
		return isMoving;
	}
	sf::Vector2f GetDirection() const {
		return direction;
	}
	float GetRotation() {
		return rotation;
	}
};

class Fireball : public Projectile {
public:
	Fireball(Player& player) 
		: Projectile(player, sf::Texture(), sf::Sprite(), 0, 0, sf::Vector2f(),
			sf::Vector2f(), 0, 0.f, 0.f, sf::CircleShape(), 0.f)
	{}

	// derived over-ridden functions
	void Initialize() override;
	void Load() override;
	void Update(sf::Vector2f dir, float rot, float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

class Arrow : public Projectile {
public:
	Arrow(Player& player)
		: Projectile(player, sf::Texture(), sf::Sprite(), 0, 0, sf::Vector2f(),
			sf::Vector2f(), 0, 0.f, 0.f, sf::CircleShape(), 0.f)
	{}

	// derived over-ridden functions
	void Initialize() override;
	void Load() override;
	void Update(sf::Vector2f dir, float rot, float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

#endif