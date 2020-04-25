#include "CharacterGoomba.h"

void CharacterGoomba::DeadUpdate(float deltaTime, SDL_Event e)
{
	mCurrentNumOfFrames = MARIOLAND_GOOMBA_DEAD_FRAME_COUNT;
	mCurrentStartFrame = MARIOLAND_GOOMBA_DEAD_START_FRAME;

	CharacterMariolandEnemy::DeadUpdate(deltaTime, e);
}

CharacterGoomba::CharacterGoomba(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float moveSpeed,
	float frameDelay, int noOfFrames, bool animating, int startFrame, int currentNumOfFrames,
	float initialJumpForce, float gravity, float jumpForceDecrement, float collisionRadius, bool screenWrapping, int scoreWorth):
	CharacterMariolandEnemy(renderer, imagePath, startPosition, map, moveSpeed, frameDelay, noOfFrames, animating, startFrame,
		currentNumOfFrames, initialJumpForce, gravity, jumpForceDecrement, collisionRadius, screenWrapping, MARIOLAND_GOOMBA_DEATH_TIMER, scoreWorth)
{
	mMovingLeft = true;

	mHitSound = new SoundEffect();
	mHitSound->Load("SFX/Marioland SFX/stomp.wav");
}

CharacterGoomba::~CharacterGoomba()
{
}