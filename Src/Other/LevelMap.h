#pragma once

#include <fstream>
#include <string>

#include "Constants.h"
#include "Commons.h"
#include "Texture2D.h"
#include "Tileset.h"

class LevelMap
{
public:
	LevelMap(SDL_Renderer* renderer, std::string imagePath, int tileWidth, int tileHeight, TILE map[MAP_HEIGHT][MAP_WIDTH]);
	LevelMap(SDL_Renderer* renderer, std::string imagePath, int tileWidth, int tileHeight, std::string mapPath);
	~LevelMap();

	TILE GetTileAt(unsigned int h, unsigned int w);
	void ChangeTileAt(unsigned int row, unsigned int column, TILE newValue);
	void Render(float yOffset);
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

