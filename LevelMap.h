#pragma once

#include <fstream>
#include <string>

#include "Constants.h"
#include "Commons.h"
#include "Texture2D.h"

class LevelMap
{
public:
	LevelMap(SDL_Renderer* renderer, std::string imagePath, TILE map[MAP_HEIGHT][MAP_WIDTH]);
	LevelMap(SDL_Renderer* renderer, std::string imagePath, std::string mapPath);
	~LevelMap();

	TILE GetTileAt(unsigned int h, unsigned int w);
	void ChangeTileAt(unsigned int row, unsigned int column, TILE newValue);
	void Render(float yOffset);
	bool TileIsPassable(TILE tile);

private:
	SDL_Renderer* mRenderer;
	Texture2D* mTexture;
	TILE** mMap;
};

