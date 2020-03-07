#pragma once

#include <SDL.h>
#include <iostream>
#include <map>
#include "Commons.h"
#include "LevelMap.h"

#include "SoundEffect.h"

class Texture2D;

class Character
{
protected:
//private:
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;
	LevelMap* mCurrentLevelMap;

	const float mMovementSpeed;
	
	SoundEffect* jumpSound;

protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	bool mJumping;
	bool mCanJump;
	float mCollisionRadius;
	float mJumpForce;


public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float moveSpeed);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	float GetCollisionRadius();
	Rect2D GetCollisionBox();
	Circle2D GetCollisionCircle();

	bool IsJumping();
	void CancelJump();

	void SetState(CHARACTERSTATE newState);
	CHARACTERSTATE GetState();

protected:
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void Jump();
	virtual void AddGravity(float deltaTime);
};

