#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>
#include "utility.h"
#include "enemy.h"
#include "player.h"
#include "map.h"

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

    inline bool CheckCircleRectCollision(const sf::CircleShape& circle,
        const sf::FloatRect& rect) {
        sf::Vector2f circleCenter = circle.getPosition();
        float radius = circle.getRadius();

        // find closest point on rectangle to the circle center
        float closestX = std::max(rect.left, std::min(circleCenter.x,
            rect.left + rect.width));
        float closestY = std::max(rect.top, std::min(circleCenter.y,
            rect.top + rect.height));

        float dx = circleCenter.x - closestX;
        float dy = circleCenter.y - closestY;
        return (dx * dx + dy * dy) <= (radius * radius);
    }

    inline void SlideEntityAlongTile(sf::Sprite& entitySprite, 
        sf::CircleShape& hitbox, float entitySpeed,
        float dt, const sf::Vector2f& normal) {
        // calculate the tangent vector
        sf::Vector2f tangent(-normal.y, normal.x);

        // Ccalculate slide offset based on speed and dt
        sf::Vector2f slideOffset = tangent * entitySpeed * dt;

        // move both the hitbox and the sprite along the tangent
        hitbox.move(slideOffset);
        entitySprite.move(slideOffset);
    }

    inline void HandleTileCollisions(sf::Sprite& entitySprite,
        sf::CircleShape& hitbox, float entitySpeed, float dt,
        const Map& map, int baseTileSize) {
        // get the entity's current position
        sf::Vector2f pos = hitbox.getPosition();

        // determine the grid cell
        int tileX = static_cast<int>(pos.x) / baseTileSize;
        int tileY = static_cast<int>(pos.y) / baseTileSize;

        // loop over nearby cells
        for (int y = tileY - 1; y <= tileY + 1; ++y) {
            for (int x = tileX - 1; x <= tileX + 1; ++x) {
                for (const auto& layer : map.layers) {
                    // check bounds
                    if (y >= 0 && y < layer.height && x >= 0 && x < layer.width) {
                        if (layer.collisionGrid[y][x]) {
                            // create a rectangle for the tile
                            sf::FloatRect tileRect(x * baseTileSize,
                                y * baseTileSize, baseTileSize, baseTileSize);
                            if (CheckCircleRectCollision(hitbox, tileRect)) {
                                sf::Vector2f circleCenter = hitbox.getPosition();
                                float closestX = std::max(tileRect.left, std::min(circleCenter.x,
                                    tileRect.left + tileRect.width));
                                float closestY = std::max(tileRect.top, std::min(circleCenter.y,
                                    tileRect.top + tileRect.height));

                                sf::Vector2f collisionVec = circleCenter - sf::Vector2f(closestX, closestY);
                                float distance = std::sqrt(collisionVec.x * collisionVec.x + collisionVec.y * collisionVec.y);
                                if (distance == 0)
                                    continue; // Avoid division by zero if center is exactly on the edge

                                sf::Vector2f normal = collisionVec / distance;

                                // Use the computed normal to slide the entity along the tile boundary
                                SlideEntityAlongTile(entitySprite, hitbox, entitySpeed, dt, normal);
                            }
                        }
                    }
                }
            }
        }
    }

}

#endif