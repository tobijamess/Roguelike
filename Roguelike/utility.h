#ifndef UTILITY_H
#define UTILITY_H

#include <SFML/Graphics.hpp>
#include "enemy.h"
#include "player.h"

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

	inline float CalculateRotation(sf::Vector2f vector) {
		float radians = atan2(vector.y, vector.x);
		// get rotation degrees by multiplying radians by 180 and dividing by pi
		float degrees = radians * (180.0f / 3.14159265359f);

		return degrees;
	}

	inline bool IsPlayerInRange(const sf::Vector2f& playerPos,
		const sf::Vector2f& enemyPos, float radius) {
		// target - current to find direction vector from player to enemy
		sf::Vector2f direction = playerPos - enemyPos;
		// get magnitude (length) of the vector
		float m = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		// if m less than or equal to radius, player is within detection/attack range
		return m <= radius;
	}
}

#endif