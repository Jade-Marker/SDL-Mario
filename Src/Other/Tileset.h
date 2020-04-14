#pragma once

#include <string>
#include <vector>
#include "Texture2D.h"
#include "Commons.h"

struct Tileset
{
	Texture2D* texture;
	int tileWidth;
	int tileHeight;
	bool tilesGoAcross;
	std::vector<TILE> passableTiles;

	Tileset(std::string imagePath, int inputTileWidth, int inputTileHeight, bool inputTilesGoAcross, std::vector<TILE> inputPassableTiles, SDL_Renderer* renderer) :
		tileWidth(inputTileWidth), tileHeight(inputTileHeight), tilesGoAcross(inputTilesGoAcross), passableTiles(inputPassableTiles)
	{
		texture = new Texture2D(renderer);
		texture->LoadFromFile(imagePath);
	}

	Tileset():
		tileWidth(0), tileHeight(0), texture(nullptr), tilesGoAcross(true)
	{
	}
};