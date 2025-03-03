#include "projectilemanager.h"

ProjectileManager::ProjectileManager(Player& plyr)
    : player(plyr), fireball(plyr), arrow(plyr)
{}

void ProjectileManager::InitializeProjectiles() {
    fireball.Initialize();
    arrow.Initialize();
}

void ProjectileManager::LoadProjectiles() {
    fireball.Load();
    arrow.Load();
}

void ProjectileManager::UpdateProjectiles(float dt) {
    for (auto& proj : projectiles) {
        proj->Update(dt);
    }
}

void ProjectileManager::DrawProjectiles(sf::RenderWindow& window) {
    for (auto& proj : projectiles) {
        proj->Draw(window);
    }
}