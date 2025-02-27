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
protected:
	int health;
	float speed;
	float hitboxScaleFactor;			// scale of the hitbox
	sf::CircleShape hitbox;				// hitbox for player
	float hitboxRadius;					// radius of hitbox
public:
	void Initialize();
	void Load();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	const sf::CircleShape GetHitbox() const {
		return hitbox;
	}
	const sf::Sprite GetSprite() const {
		return sprite;
	}
};

#endif 