#include "LevelMap.h"

LevelMap::LevelMap(SDL_Renderer* renderer, std::string imagePath, TILE map[MAP_HEIGHT][MAP_WIDTH]):
	mRenderer(renderer)
{
	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);

	//Allocate memory for the level map
	mMap = new TILE* [MAP_HEIGHT];
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		mMap[i] = new TILE[MAP_WIDTH];
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

TILE LevelMap::GetTileAt(unsigned int h, unsigned int w)
{
	if (h < MAP_HEIGHT && w < MAP_WIDTH)
	{
		return mMap[h][w];
	}
	
	return EMPTY;
}

void LevelMap::ChangeTileAt(unsigned int row, unsigned int column, TILE newValue)
{
	if (row < MAP_HEIGHT && column < MAP_WIDTH)
		mMap[row][column] = newValue;
}

void LevelMap::Render(float yOffset)
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			int left = TILE_WIDTH * mMap[y][x];

			SDL_Rect portionOfTileSet = { left, 0, TILE_WIDTH, TILE_HEIGHT };
			SDL_Rect destRect = { (int)(x * TILE_WIDTH), (int)(y * TILE_HEIGHT + yOffset), TILE_WIDTH, TILE_HEIGHT };

			mTexture->Render(portionOfTileSet, destRect, SDL_FLIP_NONE);
		}
	}
}

bool LevelMap::TileIsPassable(TILE tile)
{
	switch (tile)
	{
	case EMPTY:
	case PIPE_ENTRANCE_LOWER_RIGHT:
	case PIPE_ENTRANCE_UPPER_RIGHT:
	case PIPE_ENTRANCE_LOWER_LEFT:
	case PIPE_ENTRANCE_UPPER_LEFT:
	case PIPE_BODY_LOWER:
	case PIPE_BODY_UPPER:
		return true;

	default:
		return false;
	}
}
