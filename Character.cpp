#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float moveSpeed) :
	mRenderer(renderer), mPosition(startPosition), mFacingDirection(FACING_RIGHT),
	mMovingLeft(false), mMovingRight(false), mJumping(false), mCanJump(false), mCollisionRadius(15.0f),
	mCurrentLevelMap(map), mJumpForce(0.0f), mMovementSpeed(moveSpeed)
{
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadFromFile(imagePath);

	jumpSound = new SoundEffect();
	jumpSound->Load("SFX/Munch.wav");
}

Character::~Character()
{
	mRenderer = NULL;

	delete mTexture;
	mTexture = NULL;

	delete jumpSound;
}

void Character::Render()
{
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
		//Adjust the position
		mPosition.y -= mJumpForce * deltaTime;

		//Reduce the jump force
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		//Has the jump force reduced to zero?
		if (mJumpForce <= 0.0f)
			mJumping = false;
	}

	if (mMovingLeft)
		MoveLeft(deltaTime);
	else if (mMovingRight)
		MoveRight(deltaTime);

	int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;

	if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0)
		AddGravity(deltaTime);
	else
		mCanJump = true;
	//Collided with ground so we can jump again
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
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
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
	mPosition.x -= mMovementSpeed * deltaTime;
	mFacingDirection = FACING_LEFT;
}

void Character::MoveRight(float deltaTime)
{
	mPosition.x += mMovementSpeed * deltaTime;
	mFacingDirection = FACING_RIGHT;
}

void Character::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;

		jumpSound->Play(0);
	}
}

void Character::AddGravity(float deltaTime)
{
	mPosition.y += GRAVITY * deltaTime;
	mCanJump = false;

	if (mPosition.y > SCREEN_HEIGHT - mTexture->GetHeight())
	{
		mPosition.y = SCREEN_HEIGHT - mTexture->GetHeight();
		mCanJump = true;
	}
}
