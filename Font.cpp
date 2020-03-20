#include "Font.h"

Font::Font(SDL_Renderer* renderer, std::string fontSource, int characterWidth, int characterHeight, char firstCharacter):
	mCharacterWidth(characterWidth), mCharacterHeight(characterHeight), mFirstCharacter(firstCharacter)
{
	mFontTexture = new Texture2D(renderer);
	mFontTexture->LoadFromFile(fontSource);
}

Font::~Font()
{
}

void Font::DrawString(std::string outputString, Vector2D position)
{
	int charactersPerLine = mFontTexture->GetWidth() / mCharacterWidth;

	for (int i = 0; i < outputString.length(); i++)
	{
		char currentCharacter = outputString[i];

		int sourceX = 0, sourceY = 0;

		sourceX = ((currentCharacter - mFirstCharacter) % charactersPerLine) * mCharacterWidth;
		sourceY = ((currentCharacter - mFirstCharacter) / charactersPerLine) * mCharacterHeight;

		SDL_Rect portionOfFont = { sourceX, sourceY, mCharacterWidth, mCharacterHeight };
		SDL_Rect destRect = { (int)position.x + mCharacterWidth * i, (int)position.y, mCharacterWidth, mCharacterHeight };

		mFontTexture->Render(portionOfFont, destRect, SDL_FLIP_NONE);
	}
}
