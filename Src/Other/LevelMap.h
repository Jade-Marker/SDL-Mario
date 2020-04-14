#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "Constants.h"
#include "Commons.h"
#include "Texture2D.h"
#include "Tileset.h"

class LevelMap
{
public:
	LevelMap(SDL_Renderer* renderer, std::string imagePath, int tileWidth, int tileHeight, bool tilesGoAcross, std::vector<TILE> passableTiles, TILE map[MAP_HEIGHT][MAP_WIDTH]);
	LevelMap(SDL_Renderer* renderer, std::string imagePath, int tileWidth, int tileHeight, bool tilesGoAcross, std::vector<TILE> passableTiles, std::string mapPath);
	~LevelMap();

	TILE GetTileAt(unsigned int h, unsigned int w);
	void ChangeTileAt(unsigned int row, unsigned int column, TILE newValue);
	void Render(float yOffset, float xOffset = 0.0f);
	bool TileIsPassable(TILE tile);
	int const GetWidth() { return mMapWidth; };
	int const GetHeight() { return mMapHeight; };
	Tileset const GetTileset() { return mTileset; };

private:
	SDL_Renderer* mRenderer;
	Tileset mTileset;
	TILE** mMap;
	int mMapHeight;
	int mMapWidth;

};

