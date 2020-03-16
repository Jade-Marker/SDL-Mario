#pragma once

#include "Constants.h"
#include "Commons.h"
#include "Texture2D.h"

class LevelMap
{
public:
	LevelMap(SDL_Renderer* renderer, std::string imagePath, TILE map[MAP_HEIGHT][MAP_WIDTH]);
	~LevelMap();

	TILE GetTileAt(unsigned int h, unsigned int w);
	void ChangeTileAt(unsigned int row, unsigned int column, TILE newValue);
	void Render(float yOffset);

private:
	SDL_Renderer* mRenderer;
	Texture2D* mTexture;
	TILE** mMap;
};

