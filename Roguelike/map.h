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

inline bool LoadMap(const std::string& filename, sf::Texture& tileAtlas,
	int baseTileSize, Map& map) {
	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cerr << "Failed to open map file: " << filename << "\n";
		return false;
	}

	nlohmann::json mapData;
	file >> mapData;
	map.layers.clear();

    // iterate over each layer stored in the JSON
    for (const auto& layerData : mapData["layers"]) {
        TileLayer newLayer;
        newLayer.width = layerData["width"].get<int>();
        newLayer.height = layerData["height"].get<int>();
        newLayer.opacity = layerData["opacity"].get<float>();

        // resize the tile grid
        newLayer.tiles.resize(newLayer.height, std::vector<Tile>(newLayer.width));

        // process the "tiles" array
        const auto& tiles = layerData["tiles"];
        for (int y = 0; y < newLayer.height; ++y) {
            for (int x = 0; x < newLayer.width; ++x) {
                // skip empty tiles
                if (tiles[y][x].is_null()) continue;

                const auto& tileData = tiles[y][x];
                Tile& tile = newLayer.tiles[y][x];

                // extract the tile index
                tile.index = tileData["index"].get<int>();

                // set up the sprite
                tile.sprite.setTexture(tileAtlas);
                tile.sprite.setTextureRect(sf::IntRect(
                    tileData["textureRect"]["left"].get<int>(),
                    tileData["textureRect"]["top"].get<int>(),
                    tileData["textureRect"]["width"].get<int>(),
                    tileData["textureRect"]["height"].get<int>()
                ));
                tile.sprite.setPosition(
                    tileData["position"]["x"].get<float>(),
                    tileData["position"]["y"].get<float>()
                );
            }
        }

        // resize and load the collision grid
        newLayer.collisionGrid.resize(newLayer.height,
            std::vector<bool>(newLayer.width, false));
        const auto& collisionGridData = layerData["collisionGrid"];
        for (int y = 0; y < newLayer.height; ++y) {
            for (int x = 0; x < newLayer.width; ++x) {
                newLayer.collisionGrid[y][x] = collisionGridData[y][x].get<bool>();
            }
        }
        // add the layer to the map
        map.layers.push_back(newLayer);
    }
    return true;
}

#endif