#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "projectile.h"
#include "utility.h"
#include "player.h"

class ProjectileManager {
private:
	Player& player;

	const int projCap = 100;
	float projTimer = 0.f;
	float projCooldown = 0.15f;

	enum ProjectileType {
		FIREBALL,
		ARROW
	};

	int projType = 0;
protected:
	std::vector<std::unique_ptr<Projectile>> projectiles;
	Fireball fireball;
	Arrow arrow;
public:
	ProjectileManager(Player& plyr);
	void InitializeProjectiles();
	void LoadProjectiles();
	void UpdateProjectiles(sf::RenderWindow& window, float dt);
	void DrawProjectiles(sf::RenderWindow& window);
	void AddProjectile(std::unique_ptr<Projectile> proj) {
		projectiles.push_back(std::move(proj));
	}

	// getter for collision detection loop
	const std::vector<std::unique_ptr<Projectile>>& GetProjectiles() const {
		return projectiles;
	}
	const int& GetProjCap() const {
		return projCap;
	}
	const int& ConstGetProjCd() const {
		return projCooldown;
	}
	float GetProjTimer() const {
		return projTimer;
	}
};

#endif