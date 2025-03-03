#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "projectile.h"
#include "player.h"

class ProjectileManager {
private:
	Player& player;
	const int projCap = 1;
protected:
	std::vector<std::unique_ptr<Projectile>> projectiles;
	Fireball fireball;
	Arrow arrow;
public:
	ProjectileManager(Player& plyr);
	void InitializeProjectiles();
	void LoadProjectiles();
	void UpdateProjectiles(float dt);
	void DrawProjectiles(sf::RenderWindow& window);
	// getter for collision detection loop
	const std::vector<std::unique_ptr<Projectile>>& GetProjectiles() const {
		return projectiles;
	}
	const int GetEnemyCap() const {
		return projCap;
	}
};

#endif