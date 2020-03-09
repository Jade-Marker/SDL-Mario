#include "CharacterKoopa.h"
#include "CharacterPlayable.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed) :
	CharacterEnemy(renderer, imagePath, startPosition, map, movementSpeed)
{
	mFacingDirection = startFacing;
	//mMovementSpeed = movementSpeed;
	mPosition = startPosition;

	mInjured = false;
	mAlive = true;

	mSingleSpriteWidth = mTexture->GetWidth() / 2;	//2 sprites on this spritesheet in 1 row
	mSingleSpriteHeight = mTexture->GetHeight();
}

CharacterKoopa::~CharacterKoopa()
{
}

void CharacterKoopa::TakeDamage()
{
	mInjured = true;
	mInjuredTime = INJURED_TIME;
	Jump();
}

void CharacterKoopa::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE_SMALL;

		mJumping = true;
		mCanJump = false;
	}
}

void CharacterKoopa::Render()
{
	//Variable to hold the left position of the sprite we want to draw
	int left = 0;

	//If injured move the left position to be the left position of the second image on the spritesheet
	if (mInjured)
		left = mSingleSpriteWidth;

	//Get the portion of the spritesheet you want to draw
	//								{XPos, YPos, WidthOfSingleSprite, HeightOfSingleSprite}
	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	//Determine where you want it drawn
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	//Then draw it facing the correct direction
	if (mFacingDirection == FACING_RIGHT)
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	else
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL);
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	//To gain the benefit of the code written in the base class Update() function we need to call it
	Character::Update(deltaTime, e);

	if (!mInjured)
	{
		//We are not injured so move
		if (mFacingDirection == FACING_LEFT)
		{
			mMovingLeft = true;
			mMovingRight = false;
		}
		else if (mFacingDirection == FACING_RIGHT)
		{
			mMovingRight = true;
			mMovingLeft = false;
		}
	}
	else 
	{
		//We should not be moving when injured
		mMovingRight = false;
		mMovingLeft = false;

		//Count down the injured time
		mInjuredTime -= deltaTime;

		if (mInjuredTime <= 0.0)
			FlipRightwayUp();
	}
}

void CharacterKoopa::OnPlayerCollision(CharacterPlayable* player)
{
	/*if (mEnemies[i]->GetInjured())
		mEnemies[i]->SetAlive(false);
	else
		mMarioCharacter->SetState(PLAYER_DEATH);*/
	if (GetInjured())
		SetAlive(false);
	else
		player->SetState(PLAYER_DEATH);
}

bool CharacterKoopa::GetInjured()
{
	return mInjured;
}

void CharacterKoopa::FlipRightwayUp()
{
	if (mFacingDirection == FACING_RIGHT)
		mFacingDirection = FACING_LEFT;
	else if (mFacingDirection == FACING_LEFT)
		mFacingDirection = FACING_RIGHT;

	mInjured = false;
	Jump();
}
