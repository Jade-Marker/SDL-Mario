#include "CharacterPlayable.h"

CharacterPlayable::CharacterPlayable(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, int jumpKey, int rightKey, int leftKey, LevelMap* map, float moveSpeed):
	Character(renderer, imagePath, startPosition, map, moveSpeed), mState(IDLE), mScore(0)
{
	mInputMap[JUMP] = jumpKey;
	mInputMap[RIGHT] = rightKey;
	mInputMap[LEFT] = leftKey;
}

void CharacterPlayable::Render()
{
	if (mFacingDirection == FACING_RIGHT)
		mTexture->Render(mPosition, SDL_FLIP_NONE, 0.0);
	else
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL, 0.0);
}

void CharacterPlayable::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	int key = e.key.keysym.sym;

	//Handle any events
	switch (e.type)
	{
	case SDL_KEYDOWN:
		if (key == mInputMap[LEFT])
			mMovingLeft = true;
		else if (key == mInputMap[RIGHT])
			mMovingRight = true;
		break;

	case SDL_KEYUP:
		if (key == mInputMap[LEFT])
			mMovingLeft = false;
		else if (key == mInputMap[RIGHT])
			mMovingRight = false;
		else if (key == mInputMap[JUMP])
			Jump();
		break;
	}
}

void CharacterPlayable::OnPlayerCollision(CharacterPlayable* player)
{
	std::cout << "Colliding with other player" << std::endl;
}

void CharacterPlayable::SetState(CHARACTERSTATE newState)
{
	mState = newState;
}

CHARACTERSTATE CharacterPlayable::GetState()
{
	return mState;
}

void CharacterPlayable::IncrementScore(int value)
{
	mScore += value;
	std::cout << "Score: " << mScore << std::endl;
}