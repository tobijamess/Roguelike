#ifndef UTILITY_H
#define UTILITY_H

#include <SFML/Graphics.hpp>
#include "enemy.h"

namespace Utility {

	inline sf::Vector2f NormalizeVector(sf::Vector2f vector) {
		// use sqrt func to get magnitude (m) of the vector using the equation:
		// vector.x^2 + vector.y^2 or vector.x * vector.x + vector.y * vector.y
		float m = std::sqrt(vector.x * vector.x + vector.y * vector.y);
		sf::Vector2f normalizedVector;
		// x axis divided by the magnitude
		normalizedVector.x = vector.x / m;
		// y axis divided by the magnitude
		normalizedVector.y = vector.y / m;

		return normalizedVector;
	}

	inline bool CollisionDetection(const Player& player, const Enemy& enemy) {
		sf::Vector2f direction;
		sf::CircleShape playerHitbox = player.GetHitbox();
		sf::CircleShape enemyHitbox = enemy.GetHitbox();
		// target - current to find direction vector from player to enemy
		direction = enemyHitbox.getPosition() - playerHitbox.getPosition();
		// get magnitude or m by getting the square root of direction.x^2 + direction.y^2 (magnitude is the length)
		float m = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		// if m (length) less than or equal to 64, collision is happening (because I set both circles radius to 32)
		// check if the distance is less than or equal to the sum of the radii
		float combinedRadius = playerHitbox.getRadius() + enemyHitbox.getRadius();
		if (m <= combinedRadius) {
			return true;
		}
		else {
			return false;
		}
	}
}


#endif