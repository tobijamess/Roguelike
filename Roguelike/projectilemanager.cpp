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

void ProjectileManager::UpdateProjectiles(sf::RenderWindow& window, float dt) {
    projTimer += dt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        projType = FIREBALL;
        std::cout << "Fireball active.\n";
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        projType = ARROW;
        std::cout << "Arrow active.\n";
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
        && projTimer >= projCooldown) {

        projTimer = 0.f;

        std::unique_ptr<Projectile> proj;

        // use default view for mousepos mapping otherwise projectiles will fire with an offset
        sf::View defaultView = window.getDefaultView();
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::Vector2f direction = mousePos - player.ConstGetSprite().getPosition();
        direction = Utility::NormalizeVector(direction);
        float rotation = Utility::CalculateRotation(direction);
        
        if (projType == FIREBALL) {
            proj = std::make_unique<Fireball>(player);
            std::cout << "Fireball created.\n";
        }
        else if (projType == ARROW) {
            proj = std::make_unique<Arrow>(player);
            std::cout << "Arrow created.\n";
        }
        proj->Initialize();
        proj->Load();
        proj->SetPosition(player.ConstGetSprite().getPosition());
        proj->Fire();
        proj->Update(direction, rotation, dt);

        AddProjectile(std::move(proj));
    }

    for (auto& proj : projectiles) {
        if (proj->IsFired()) {
            proj->Update(proj->GetDirection(), proj->GetRotation(), dt);
        }
    }

    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
            [](const std::unique_ptr<Projectile>& proj) {
                return !proj->IsFired();
            }
        ),
        projectiles.end()
    );
}

void ProjectileManager::DrawProjectiles(sf::RenderWindow& window) {
    for (auto& proj : projectiles) {
        proj->Draw(window);
    }
}