#include "LevelMap.h"

LevelMap::LevelMap(SDL_Renderer* renderer, std::string imagePath, int tileWidth, int tileHeight, TILE map[MAP_HEIGHT][MAP_WIDTH]):
	mRenderer(renderer), mMapHeight(MAP_HEIGHT), mMapWidth(MAP_WIDTH)
{
	mTileset = Tileset(imagePath, tileWidth, tileHeight, mRenderer);

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

LevelMap::LevelMap(SDL_Renderer* renderer, std::string imagePath, int tileWidth, int tileHeight, std::string mapPath):
	mRenderer(renderer)
{
	mTileset = Tileset(imagePath, tileWidth, tileHeight, mRenderer);

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
			if (mMap[y][x] != EMPTY)
			{
				int left = mTileset.tileWidth * mMap[y][x];

				SDL_Rect portionOfTileSet = { left, 0, mTileset.tileWidth, mTileset.tileHeight };
				SDL_Rect destRect = { (int)(x * mTileset.tileWidth), (int)(y * mTileset.tileHeight + yOffset), mTileset.tileWidth, mTileset.tileHeight };

				mTileset.texture->Render(portionOfTileSet, destRect, SDL_FLIP_NONE);
			}
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
