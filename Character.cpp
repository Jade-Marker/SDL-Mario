#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"
#include "CharacterPlayable.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float moveSpeed, float frameDelay, int noOfFrames, bool animating) :
	mRenderer(renderer), mPosition(startPosition), mFacingDirection(FACING_RIGHT),
	mMovingLeft(false), mMovingRight(false), mJumping(false), mCanJump(false), mCollisionRadius(15.0f),
	mCurrentLevelMap(map), mJumpForce(0.0f), cMovementSpeed(moveSpeed), 
	mFrameDelay(frameDelay), mNumFrames(noOfFrames), mAnimating(animating), mCurrentFrame(0), mSingleSpriteWidth(0), mSingleSpriteHeight(0)
{
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadFromFile(imagePath);

	mJumpSound = new SoundEffect();
	mJumpSound->Load("SFX/Munch.wav");

	mSingleSpriteWidth = mTexture->GetWidth() / noOfFrames;
	mSingleSpriteHeight = mTexture->GetHeight();
}

Character::~Character()
{
	mRenderer = NULL;

	delete mTexture;
	mTexture = NULL;

	delete mJumpSound;
}

void Character::Render()
{
	int left = mCurrentFrame * mSingleSpriteWidth;

	//Get the portion of the spritesheet you want to draw
	//								{XPos, YPos, WidthOfSingleSprite, HeightOfSingleSprite}
	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	if (mFacingDirection == FACING_RIGHT)
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	else
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL);
}

void Character::Update(float deltaTime, SDL_Event e)
{
	int key = e.key.keysym.sym;

	//Handle any events
	switch (e.type)
	{
	}

	//Deal with jumping first
	if (mJumping)
	{
		if (mCurrentLevelMap->GetTileAt(mPosition.y / TILE_HEIGHT, (mPosition.x + (mSingleSpriteWidth * 0.5f)) / TILE_WIDTH) == EMPTY) {

			//Adjust the position
			mPosition.y -= mJumpForce * deltaTime;

			//Reduce the jump force
			mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

			//Has the jump force reduced to zero?
			if (mJumpForce <= 0.0f)
				mJumping = false;
		}
		else
			mJumping = false;
	}

	if (mMovingLeft)
		MoveLeft(deltaTime);
	else if (mMovingRight)
		MoveRight(deltaTime);

	int centralXPosition = (int)(roundf(mPosition.x + (mSingleSpriteWidth * 0.5f))) / TILE_WIDTH;
	int footPosition = (int)(mPosition.y + mSingleSpriteHeight) / TILE_HEIGHT;
	
	if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == EMPTY)
		AddGravity(deltaTime);
	else
		mCanJump = true;
	//Collided with ground so we can jump again

	if (mNumFrames > 1 && mAnimating)
	{
		mFrameDelay -= deltaTime;
		if (mFrameDelay <= 0.0f)
		{
			//Reset frame delay count
			mFrameDelay = ANIMATION_DELAY;
			mCurrentFrame++;

			//Loop frame around if it goes beyond the number of frames
			if (mCurrentFrame > mNumFrames - 1)
				mCurrentFrame = 0;
		}
	}
}

void Character::OnPlayerCollision(CharacterPlayable* player)
{
}

void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D Character::GetPosition()
{
	return mPosition;
}

float Character::GetCollisionRadius()
{
	return mCollisionRadius;
}

Rect2D Character::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mSingleSpriteHeight);
}

Circle2D Character::GetCollisionCircle()
{
	return Circle2D(mPosition.x, mPosition.y, mCollisionRadius);
}

bool Character::IsJumping()
{
	return mJumping;
}

void Character::CancelJump()
{
	mJumping = false;
	mCanJump = true;
}

void Character::MoveLeft(float deltaTime)
{
	int xPos = (int)(roundf(mPosition.x - mSingleSpriteWidth * 0.5f)) / TILE_WIDTH;
	int yPosUpper = (int)(roundf(mPosition.y)) / TILE_HEIGHT;
	int yPosMid = (int)(roundf(mPosition.y + mSingleSpriteHeight * 0.5f)) / TILE_HEIGHT;
	int yPosLower = (int)(roundf(mPosition.y + mSingleSpriteHeight * 0.75f)) / TILE_HEIGHT;

	mFacingDirection = FACING_LEFT;
	if (mCurrentLevelMap->GetTileAt(yPosUpper, xPos) == EMPTY && mCurrentLevelMap->GetTileAt(yPosMid, xPos) == EMPTY && mCurrentLevelMap->GetTileAt(yPosLower, xPos) == EMPTY)
	{
		mPosition.x -= cMovementSpeed * deltaTime;
	}
}

void Character::MoveRight(float deltaTime)
{
	int xPos = (int)(roundf(mPosition.x + mSingleSpriteWidth * 1.5f)) / TILE_WIDTH;
	int yPosUpper = (int)(roundf(mPosition.y)) / TILE_HEIGHT;
	int yPosMid = (int)(roundf(mPosition.y + mSingleSpriteHeight * 0.5f)) / TILE_HEIGHT;
	int yPosLower = (int)(roundf(mPosition.y + mSingleSpriteHeight * 0.75f)) / TILE_HEIGHT;

	mFacingDirection = FACING_RIGHT;
	if (mCurrentLevelMap->GetTileAt(yPosUpper, xPos) == EMPTY && mCurrentLevelMap->GetTileAt(yPosMid, xPos) == EMPTY && mCurrentLevelMap->GetTileAt(yPosLower, xPos) == EMPTY)
	{
		mPosition.x += cMovementSpeed * deltaTime;
	}
}

void Character::Jump()
{
	if (!mJumping && mCanJump)
	{
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;

		mJumpSound->Play(0);
	}
}

void Character::AddGravity(float deltaTime)
{
	mPosition.y += GRAVITY * deltaTime;
	mCanJump = false;

	if (mPosition.y > SCREEN_HEIGHT - mSingleSpriteHeight)
	{
		mPosition.y = SCREEN_HEIGHT - mSingleSpriteHeight;
		mCanJump = true;
	}
}
