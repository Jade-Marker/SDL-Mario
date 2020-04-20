#pragma once
#include "CharacterEnemy.h"
#include "CharacterPlayable.h"

enum FLY_STATE
{
	FLY_MOVING,
	FLY_DEAD
};

class CharacterFly :
	public CharacterEnemy
{
private:
	SoundEffect* mHitSound;
	float mJumpTimer;
	CharacterPlayable* mMario;
	FACING mJumpDirection;
	FLY_STATE mState;
	float mDeathTimer;

public:
	CharacterFly(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float moveSpeed,
		float frameDelay, int noOfFrames, bool animating, int startFrame, int currentNumOfFrames,
		float initialJumpForce, float gravity, float jumpForceDecrement, float collisionRadius, CharacterPlayable* mario);

	void Update(float deltaTime, SDL_Event e);
	void OnPlayerCollision(CharacterPlayable* player);
};

