#pragma once

#include "Texture2D.h"

class Font
{
private:
	Texture2D* mFontTexture;
	int mCharacterWidth;
	int mCharacterHeight;
	char mFirstCharacter;

public:
	Font(SDL_Renderer* renderer, std::string fontSource, int characterWidth, int characterHeight, char firstCharacter);
	~Font();

	void DrawString(std::string outputString, Vector2D position, Vector2D scale);
};

