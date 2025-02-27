#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>
#include "utility.h"
#include "enemy.h"
#include "player.h"

namespace Collision {

	inline bool CollisionDetection(const Player& player, const Enemy& enemy) {
		sf::Vector2f direction;
		sf::CircleShape playerHitbox = player.ConstGetHitbox();
		sf::CircleShape enemyHitbox = enemy.ConstGetHitbox();
		// target - current to find direction vector from player to enemy
		direction = enemyHitbox.getPosition() - playerHitbox.getPosition();
		// get magnitude (length) of the vector
		float m = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		// if m less than or equal to radii sum, collision is happening
		float combinedRadius = playerHitbox.getRadius() + enemyHitbox.getRadius();
        return m <= combinedRadius;
	}

    inline bool PlayerEnemyCollision(Player& player, Enemy& enemy,
        float dt, bool isMoving) {

        if (CollisionDetection(player, enemy)) {
            // get hitbox positions
            sf::Vector2f playerPos = player.ConstGetHitbox().getPosition();
            sf::Vector2f enemyPos = enemy.ConstGetHitbox().getPosition();
            sf::Vector2f direction = enemyPos - playerPos;

            // compute collision boundary
            float playerRadius = player.ConstGetHitbox().getRadius();
            float enemyRadius = enemy.ConstGetHitbox().getRadius();
            float collisionBoundary = playerRadius + enemyRadius;
    
            direction = Utility::NormalizeVector(direction);
            float distance = std::sqrt(direction.x * direction.x
                + direction.y * direction.y);
            sf::Vector2f boundaryPos = enemyPos - direction * collisionBoundary;

            // if collision detected and distance is valid
            if (distance < collisionBoundary) {
                player.GetHitbox().setPosition(boundaryPos);
                player.GetSprite().setPosition(boundaryPos);
            }
            // if the player is moving, apply a slide along collision boundary
            if (isMoving) {
                sf::Vector2f tangent(-direction.y, direction.x);
                sf::Vector2f slideOffset = tangent * player.ConstGetSpeed() * dt;
                player.Move(slideOffset);
            }
            return true;
        }
        return false;
    }
}

#endif