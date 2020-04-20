#pragma once

#include <SDL.h>
#include <iostream>
#include <map>
#include "Commons.h"
#include "LevelMap.h"

#include "SoundEffect.h"
#include "Collisions.h"

class Texture2D;
class CharacterPlayable;

class Character
{
protected:
	//movement variables
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;
	Vector2D mPosition;

	//constant movement variables
	const float cMovementSpeed;
	const float cInitialJumpForce;
	const float cGravity;
	const float cJumpForceDecrement;

	//jumping variables
	bool mJumping;
	bool mCanJump;
	float mJumpForce;
	SoundEffect* mJumpSound;

	//collision variables
	float mCollisionRadius;

	//Level variables
	LevelMap* mCurrentLevelMap;
	bool mScreenWrappingEnabled;
	
	//Display variables
	SDL_Renderer* mRenderer;
	Texture2D* mTexture;

	//Animation variables
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	float mFrameDelayTimer;
	float mFrameDelay;
	int mCurrentFrame;
	int mNumFrames;
	bool mAnimating;
	int mCurrentStartFrame;
	int mCurrentNumOfFrames;

public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float moveSpeed, float initialJumpForce, float gravity, float jumpForceDecrement, float collisionRadius,
		float frameDelay = 0.0f, int noOfFrames = 1, bool animating = true, int currentStartFrame = 0, int currentNumOfFrames = 1, bool screenWrappingEnabled = true);
	virtual ~Character();

	virtual void Render(int xOffset = 0);
	virtual void Update(float deltaTime, SDL_Event e);
	virtual void OnPlayerCollision(CharacterPlayable* player);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	float GetCollisionRadius();
	Rect2D GetCollisionBox();
	Circle2D GetCollisionCircle();

	bool IsJumping();
	bool CanJump() { return mCanJump; };
	void CancelJump();

	float GetWidth() { return mSingleSpriteWidth; };
	float GetHeight() { return mSingleSpriteHeight; };

protected:
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void Jump();
	virtual void AddGravity(float deltaTime);
	virtual void HitTile();
	virtual void ScreenWrap(float deltaTime);
};

