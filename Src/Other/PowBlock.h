#pragma once

#include <SDL.h>
#include "Commons.h"
#include "LevelMap.h"
#include "Texture2D.h"

class PowBlock
{
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* map);
	~PowBlock();
	void Render();
	void TakeAHit();
	bool IsAvailable() { return mNumberOfHitsLeft > 0; };
	Rect2D GetCollisionBox() {
		return Rect2D(
			mPosition.x - mSingleSpriteWidth * POW_COLLISION_INCREASE, mPosition.y,
			mSingleSpriteWidth + 2 * POW_COLLISION_INCREASE * mSingleSpriteWidth, mSingleSpriteHeight + POW_COLLISION_INCREASE * mSingleSpriteHeight);
	};

private:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	int mNumberOfHitsLeft;
};

