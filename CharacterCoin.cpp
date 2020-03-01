#include "CharacterCoin.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING moveDirection, float movementSpeed):
	Character(renderer, imagePath, startPosition, 0, 0, 0, map, movementSpeed)
{
	mPosition = startPosition;

	mAlive = true;

	mSingleSpriteWidth = mTexture->GetWidth() / 5;	//3 sprites on this spritesheet in 1 row
	mSingleSpriteHeight = mTexture->GetHeight();

	if (moveDirection == FACING_LEFT)
		mMovingLeft = true;
	else
		mMovingRight = true;

	mFrameDelay = ANIMATION_DELAY;
	mCurrentFrame = 0;
}

CharacterCoin::~CharacterCoin()
{
}

void CharacterCoin::Render()
{
	//Variable to hold the left position of the sprite we want to draw
	int left = mCurrentFrame * mSingleSpriteWidth;

	//Get the portion of the spritesheet you want to draw
	//								{XPos, YPos, WidthOfSingleSprite, HeightOfSingleSprite}
	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	//Determine where you want it drawn
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
}

void CharacterCoin::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	//Change frame?
	mFrameDelay -= deltaTime;
	if (mFrameDelay <= 0.0f)
	{
		//Reset frame delay count
		mFrameDelay = ANIMATION_DELAY;
		mCurrentFrame++;

		//Loop frame around if it goes beyond the number of frames
		if (mCurrentFrame > 4)
			mCurrentFrame = 0;
	}
}

void CharacterCoin::SetAlive(bool value)
{
}

bool CharacterCoin::GetAlive()
{
	return false;
}
