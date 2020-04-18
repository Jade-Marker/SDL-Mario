#pragma once

#include "Character.h"
#include "SoundList.h"

class CharacterEnemy :
	public Character
{
protected:
	bool mAlive;
	SoundEffect* mDeathSound;

public:
	CharacterEnemy(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float moveSpeed,
		float frameDelay, int noOfFrames, bool animating, int startFrame, int currentNumOfFrames,
		float initialJumpForce, float gravity, float jumpForceDecrement);
	virtual ~CharacterEnemy();

	virtual void TakeDamage();
	void SetAlive(bool value);
	bool GetAlive();

};

