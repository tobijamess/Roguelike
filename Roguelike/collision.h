#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>
#include "utility.h"
#include "enemy.h"
#include "player.h"
#include "map.h"

namespace Collision {

	inline bool CheckCircleCollision(const sf::CircleShape& a, const sf::CircleShape& b) {
        sf::Vector2f delta = a.getPosition() - b.getPosition();
        float distanceSquared = delta.x * delta.x + delta.y * delta.y;
        float radiiSum = a.getRadius() + b.getRadius();
        return distanceSquared <= radiiSum * radiiSum;
	}

    inline bool PlayerEnemyCollision(Player& player, Enemy& enemy,
        float dt, bool isMoving) {

        if (CheckCircleCollision(player.ConstGetHitbox(), enemy.ConstGetHitbox())) {
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

    // adjusts the entity pos by subtracting the minimum translation vector
    // so it sits flush with tiles
    inline void HandleTileCollisionsMTV(sf::Sprite& entitySprite,
        sf::CircleShape& hitbox, float entitySpeed, float dt,
        const Map& map, int baseTileSize, bool isMoving,
        const std::function<void()>& OnCollision = nullptr) {

        // get the entities current pos and determine grid cell pos
        sf::Vector2f pos = hitbox.getPosition();
        int tileX = static_cast<int>(pos.x) / baseTileSize;
        int tileY = static_cast<int>(pos.y) / baseTileSize;

        // loop over nearby grid cells
        for (int y = tileY - 1; y <= tileY + 1; ++y) {
            for (int x = tileX - 1; x <= tileX + 1; ++x) {
                for (const auto& layer : map.layers) {
                    if (y >= 0 && y < layer.height && x >= 0 && x < layer.width) {
                        if (layer.collisionGrid[y][x]) {
                            sf::FloatRect tileRect(x * baseTileSize,
                                y * baseTileSize, baseTileSize, baseTileSize);
                            if (CheckCircleRectCollision(hitbox, tileRect)) {
                                // find closest point on the tile to circle midpoint
                                sf::Vector2f circleMidpoint = hitbox.getPosition();
                                float closestX = std::max(tileRect.left,
                                    std::min(circleMidpoint.x, tileRect.left
                                        + tileRect.width));
                                float closestY = std::max(tileRect.top,
                                    std::min(circleMidpoint.y, tileRect.top
                                        + tileRect.height));

                                // calculate the collision vector from tile to circle
                                sf::Vector2f collisionVec = circleMidpoint 
                                    - sf::Vector2f(closestX, closestY);
                                float distance = 
                                    std::sqrt(collisionVec.x * collisionVec.x
                                        + collisionVec.y * collisionVec.y);

                                if (distance == 0.f)
                                    continue;

                                // normalize to get collision normal
                                sf::Vector2f normal = collisionVec / distance;

                                // find penetration depth
                                float pen = hitbox.getRadius() - distance;
                                if (pen > 0.f) {
                                    sf::Vector2f MTV = normal * pen;
                                    entitySprite.move(MTV);
                                    hitbox.move(MTV);

                                    if (OnCollision) {
                                        OnCollision();
                                    }
                                    else if (isMoving) {
                                        sf::Vector2f tangent(-normal.y, normal.x);
                                        sf::Vector2f slideOffset =
                                            tangent * entitySpeed * dt;
                                        entitySprite.move(slideOffset);
                                        hitbox.move(slideOffset);
                                    }

                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

#endif