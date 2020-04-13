#pragma once

#include <string>
#include "Texture2D.h"

struct Tileset
{
	Texture2D* texture;
	int tileWidth;
	int tileHeight;

	Tileset(std::string imagePath, int inputTileWidth, int inputTileHeight, SDL_Renderer* renderer) :
		tileWidth(inputTileWidth), tileHeight(inputTileHeight)
	{
		texture = new Texture2D(renderer);
		texture->LoadFromFile(imagePath);
	}

	Tileset():
		tileWidth(0), tileHeight(0), texture(nullptr)
	{
	}
};