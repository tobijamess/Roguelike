#ifndef TOROIDALGENERATION_H
#define TOROIDALGENERATION_H

#include <SFML/Graphics.hpp>
#include "map.h"

namespace Toroidal {

	inline sf::Vector2f WrapPosition(const sf::Vector2f& pos, const Map& map,
		int baseTileSize) {
		
		int mapWidth = map.layers[0].width * baseTileSize;
		int mapHeight = map.layers[0].height * baseTileSize;

		sf::Vector2f wrapped = pos;

		// if x coord is < 0, add map width so entity pos moves to opposite side
		if (wrapped.x < 0) {
			wrapped.x += mapWidth;
		}
		else if (wrapped.x >= mapWidth) {
			wrapped.x -= mapWidth;
		}
		// if y coord is < 0 add map height so entity pos moves to opposite side
		if (wrapped.y < 0) {
			wrapped.y += mapHeight;
		}
		else if (wrapped.y >= mapHeight) {
			wrapped.y -= mapHeight;
		}
		
		return wrapped;
	}

	// helper for wrapping entities 
	inline void WrapEntity(sf::Sprite& sprite, sf::CircleShape& hitbox,
		const Map& map, int baseTileSize) {
		sf::Vector2f pos = WrapPosition(sprite.getPosition(), map, baseTileSize);
		sprite.setPosition(pos);
		hitbox.setPosition(pos);
	}
}

#endif