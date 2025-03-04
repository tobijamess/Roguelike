#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream> 

class Player {
private:
	sf::Texture texture;				// spritesheet texture
	sf::Sprite sprite;					// player sprite
	int xSpriteIndex;					// x index of sprite texture
	int ySpriteIndex;					// y index of sprite texture
	sf::Vector2f spriteSize;			// size of the sprite in px
	sf::Vector2f playerScaleFactor;		// scale of the sprite
	bool isMoving;						// track if player is moving
protected:
	int health;
	float speed;
	float hitboxScaleFactor;			// scale of the hitbox
	sf::CircleShape hitbox;				// hitbox for player
	float hitboxRadius;					// radius of hitbox
public:
	Player();
	void Initialize();
	void Load();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
	void Move(const sf::Vector2f& offset);
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
	const bool& GetMovingStatus() const {
		return isMoving;
	}

	int TakeDamage(int damage) {
		return health -= damage;
	}
};

#endif 