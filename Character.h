#pragma once

#include <SDL.h>
#include <iostream>
#include <map>
#include "Commons.h"
#include "LevelMap.h"

#include "SoundEffect.h"

class Texture2D;
class CharacterPlayable;

class Character
{
protected:
//private:
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;
	LevelMap* mCurrentLevelMap;

	const float mMovementSpeed;
	
	SoundEffect* mJumpSound;

protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	bool mJumping;
	bool mCanJump;
	float mCollisionRadius;
	float mJumpForce;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	float mFrameDelay;
	int mCurrentFrame;
	int mNumFrames;
	bool mAnimating;

public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float moveSpeed, float frameDelay = 0.0f, int noOfFrames = 0, bool animating = true);
	virtual ~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	virtual void OnPlayerCollision(CharacterPlayable* player);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	float GetCollisionRadius();
	Rect2D GetCollisionBox();
	Circle2D GetCollisionCircle();

	bool IsJumping();
	void CancelJump();

protected:
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void Jump();
	virtual void AddGravity(float deltaTime);
};

