#include "initialization.h"
#include "enemymanager.h"
#include "player.h"
#include "projectile.h"

void Initialization::Initialize() {
	EnemyManager enemyManager;
	enemyManager.InitializeEnemies();
	Player player;
	player.Initialize();
}