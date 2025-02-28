#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include "json.hpp"
#include <fstream>
#include <iostream>

struct Tile {
	int index = -1;
	sf::Sprite sprite;
};

struct TileLayer {
	int width;
	int height;
	float opacity;
	std::vector<std::vector<Tile>> tiles;
	std::vector<std::vector<bool>> collisionGrid;
};

struct Map {
	std::vector<TileLayer> layers;
};

bool LoadMap(const std::string& filename, sf::Texture& tileAtlas,
	int baseTileSize, Map& map) {
	std::ifstream inFile(filename);

	if (!inFile.is_open()) {
		std::cerr << "Failed to open map file: " << filename << "\n";
		return false;
	}

	nlohmann::json j;
	inFile >> j;

	if (!j.contains("layers")) {
		std::cerr << "Map file is missing layer data.\n";
		return false;
	}

	map.layers.clear();

	for (auto& layerJSON : j["layers"]) {
		TileLayer layer;
		layer.width = layerJSON["width"].get<int>();
		layer.height = layerJSON["height"].get<int>();
		layer.opacity = layerJSON["opacity"].get<float>();

		layer.tiles.resize(layer.height, std::vector<Tile>(layer.width));
		layer.collisionGrid.resize(layer.height,
			std::vector<bool>(layer.width, false));

		auto tilesJSON = layerJSON["tiles"];

		for (int y = 0; y < layer.height; ++y) {
			for (int x = 0; x < layer.width; ++x) {
				int tileIndex = tilesJSON[y][x].get<int>();
				layer.tiles[y][x].index = tileIndex;

				if (tileIndex >= 0) {
					int tilesPerRow = tileAtlas.getSize().x / baseTileSize;
					int tileX = tileIndex % tilesPerRow;
					int tileY = tileIndex / tilesPerRow;
					sf::IntRect texRect(tileX * baseTileSize, tileY * baseTileSize,
						baseTileSize, baseTileSize);

					layer.tiles[y][x].sprite.setTexture(tileAtlas);
					layer.tiles[y][x].sprite.setTextureRect(texRect);
					layer.tiles[y][x].sprite.setPosition(static_cast<float>(
						x * baseTileSize), static_cast<float>(y * baseTileSize));

					sf::Color color = layer.tiles[y][x].sprite.getColor();
					color.a = static_cast<sf::Uint8>(layer.opacity * 255);
					layer.tiles[y][x].sprite.setColor(color);
				}
			}
		}

		auto collisionJSON = layerJSON["collision"];

		for (int y = 0; y < layer.height; ++y) {
			for (int x = 0; x < layer.width; ++x) {
				layer.collisionGrid[y][x] = collisionJSON[y][x].get<bool>();
			}
		}

		map.layers.push_back(layer);
	}
	return true;
}

#endif