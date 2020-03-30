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

	//jumping variables
	bool mJumping;
	bool mCanJump;
	float mJumpForce;
	SoundEffect* mJumpSound;

	//collision variables
	float mCollisionRadius;

	//Level variables
	LevelMap* mCurrentLevelMap;
	
	//Display variables
	SDL_Renderer* mRenderer;
	Texture2D* mTexture;

	//Animation variables
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	float mFrameDelay;
	int mCurrentFrame;
	int mNumFrames;
	bool mAnimating;

public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float moveSpeed, float frameDelay = 0.0f, int noOfFrames = 1, bool animating = true);
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
	virtual void HitTile();
	virtual void ScreenWrap(float deltaTime);
};

