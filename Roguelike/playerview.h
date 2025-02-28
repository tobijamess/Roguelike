#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include <SFML/Graphics.hpp>

namespace PlayerView {

	inline sf::View playerView;

	inline void SetUpPlayerView(Player& player, sf::RenderWindow& window) {

		playerView.setSize(window.getSize().x, window.getSize().y);

		// get the player's current position
		sf::Vector2f playerPos = player.GetSprite().getPosition();

		// retrieve the mouse position in window coordinates
		sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);

		// convert the mouse position to world coordinates
		sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);

		// compute an offset: scale the difference between the mouse and player
		// positions, the factor controls how much the view shifts
		sf::Vector2f offset = (mouseWorldPos - playerPos) * 0.1f;

		const float maxOffset = 100.f;
		if (std::sqrt(offset.x * offset.x + offset.y * offset.y) > maxOffset) {
			offset = (offset / std::sqrt(offset.x * offset.x + offset.y * offset.y)) * maxOffset;
		}

		playerView.setCenter(playerPos + offset);
		playerView.zoom(0.5f);
		window.setView(playerView);
	}
}

#endif