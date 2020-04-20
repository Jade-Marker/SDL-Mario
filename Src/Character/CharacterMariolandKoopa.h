#pragma once
#include "CharacterMariolandEnemy.h"
class CharacterMariolandKoopa :
	public CharacterMariolandEnemy
{
private:
	bool explosionSoundPlayed;
	SoundEffect* mExplodeSound;
	float mPercentageDead;

	virtual void DeadUpdate(float deltaTime, SDL_Event e);

public:
	CharacterMariolandKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float moveSpeed,
		float frameDelay, int noOfFrames, bool animating, int startFrame, int currentNumOfFrames,
		float initialJumpForce, float gravity, float jumpForceDecrement, float collisionRadius, bool screenWrapping = true, float deathTime = 0.0f);
	~CharacterMariolandKoopa();

	virtual void OnPlayerCollision(CharacterPlayable* player);
};

