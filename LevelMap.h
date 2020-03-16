#pragma once

#include "Constants.h"
#include "Commons.h"

class LevelMap
{
public:
	LevelMap(COLLISION_TILE map[MAP_HEIGHT][MAP_WIDTH]);
	~LevelMap();

	COLLISION_TILE GetTileAt(unsigned int h, unsigned int w);
	void ChangeTileAt(unsigned int row, unsigned int column, COLLISION_TILE newValue);

private:
	COLLISION_TILE** mMap;
};

