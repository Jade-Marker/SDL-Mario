#pragma once
#include "CharacterEnemy.h"
class CharacterQMarkCoin :
	public CharacterEnemy
{
private:
	float mAliveTimer;
	SoundEffect* collectSound;

public:
	CharacterQMarkCoin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float moveSpeed,
		float frameDelay, int noOfFrames, bool animating, int startFrame, int currentNumOfFrames,
		float initialJumpForce, float jumpForceDecrement, float collisionRadius, float aliveTime);
	~CharacterQMarkCoin();

	virtual void Update(float deltaTime, SDL_Event e);
};

