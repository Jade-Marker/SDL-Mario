#pragma once
#include "CharacterEnemy.h"
#include "CharacterPlayable.h"

enum GOOMBA_STATE 
{
	GOOMBA_MOVING, 
	GOOMBA_DEAD
};

class CharacterGoomba :
	public CharacterEnemy
{
private:
	GOOMBA_STATE mState;
	float mDeadTimer;
	SoundEffect* mHitSound;

public:
	CharacterGoomba(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float moveSpeed,
		float frameDelay, int noOfFrames, bool animating, int startFrame, int currentNumOfFrames,
		float initialJumpForce, float gravity, float jumpForceDecrement, float collisionRadius, bool screenWrapping);
	~CharacterGoomba();

	void Update(float deltaTime, SDL_Event e);
	void OnPlayerCollision(CharacterPlayable* player);
};

