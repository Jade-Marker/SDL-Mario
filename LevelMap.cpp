#include "LevelMap.h"

//When making a map, remember:
//0 = Empty area, 1 = Blocked area
LevelMap::LevelMap(COLLISION_TILE map[MAP_HEIGHT][MAP_WIDTH])
{
	//Allocate memory for the level map
	mMap = new COLLISION_TILE* [MAP_HEIGHT];
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		mMap[i] = new COLLISION_TILE[MAP_WIDTH];
	}

	//Populate the array
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			mMap[i][j] = map[i][j];
		}
	}
}

LevelMap::~LevelMap()
{
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		delete[] mMap[i];
	}

	delete[]mMap;
}

COLLISION_TILE LevelMap::GetTileAt(unsigned int h, unsigned int w)
{
	if (h < MAP_HEIGHT && w < MAP_WIDTH)
	{
		return mMap[h][w];
	}
	
	return EMPTY;
}

void LevelMap::ChangeTileAt(unsigned int row, unsigned int column, COLLISION_TILE newValue)
{
	if (row < MAP_HEIGHT && column < MAP_WIDTH)
		mMap[row][column] = newValue;
}
