#include "LevelMap.h"

LevelMap::LevelMap(SDL_Renderer* renderer, std::string imagePath, TILE map[MAP_HEIGHT][MAP_WIDTH]):
	mRenderer(renderer), mMapHeight(MAP_HEIGHT), mMapWidth(MAP_WIDTH)
{
	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);

	//Allocate memory for the level map
	mMap = new TILE* [mMapHeight];
	for (unsigned int i = 0; i < mMapHeight; i++)
	{
		mMap[i] = new TILE[mMapWidth];
	}

	//Populate the array
	for (unsigned int i = 0; i < mMapHeight; i++)
	{
		for (unsigned int j = 0; j < mMapWidth; j++)
		{
			mMap[i][j] = map[i][j];
		}
	}
}

LevelMap::LevelMap(SDL_Renderer* renderer, std::string imagePath, std::string mapPath):
	mRenderer(renderer)
{
	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);

	std::ifstream inFile(mapPath);
	inFile >> mMapHeight;
	inFile >> mMapWidth;

	//Allocate memory for the level map
	mMap = new TILE * [mMapHeight];
	for (unsigned int i = 0; i < mMapHeight; i++)
	{
		mMap[i] = new TILE[mMapWidth];
	}

	std::string tile;
	for (int y = 0; y < mMapHeight; y++)
	{
		for (int x = 0; x < mMapWidth; x++)
		{
			std::getline(inFile, tile, ',');	//file is a csv, so using ',' as the delimiter means that each getline gives us an individual tile
			mMap[y][x] = (TILE)std::stoi(tile);
		}
	}
}

LevelMap::~LevelMap()
{
	for (unsigned int i = 0; i < mMapHeight; i++)
	{
		delete[] mMap[i];
	}

	delete[]mMap;
}

TILE LevelMap::GetTileAt(unsigned int h, unsigned int w)
{
	if (h < mMapHeight && w < mMapWidth)
	{
		return mMap[h][w];
	}
	
	return EMPTY;
}

void LevelMap::ChangeTileAt(unsigned int row, unsigned int column, TILE newValue)
{
	if (row < mMapHeight && column < mMapWidth)
		mMap[row][column] = newValue;
}

void LevelMap::Render(float yOffset)
{
	for (int y = 0; y < mMapHeight; y++)
	{
		for (int x = 0; x < mMapWidth; x++)
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
