#include "CharacterMariolandKoopa.h"

void CharacterMariolandKoopa::DeadUpdate(float deltaTime, SDL_Event e)
{
	mCurrentNumOfFrames = 1;

	mPercentageDead = mDeathTimer / DEATH_TIME;

	if (mPercentageDead <= 0.25f)
		mCurrentStartFrame = MARIOLAND_KOOPA_DEATH_ANIM1_FRAME;
	else if (mPercentageDead <= 0.75f)
		mCurrentStartFrame = MARIOLAND_KOOPA_DEATH_ANIM1_FRAME + (int)(100 * mPercentageDead) % 2;
	else
	{
		if (!explosionSoundPlayed)
		{
			mExplodeSound->Play(0);
			explosionSoundPlayed = true;
		}

		mCurrentFrame = MARIOLAND_KOOPA_DEATH_ANIM2_FRAME + (int)(100 * mPercentageDead) % 2;
	}

	CharacterMariolandEnemy::DeadUpdate(deltaTime, e);
}

CharacterMariolandKoopa::CharacterMariolandKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float moveSpeed,
	float frameDelay, int noOfFrames, bool animating, int startFrame, int currentNumOfFrames,
	float initialJumpForce, float gravity, float jumpForceDecrement, float collisionRadius, bool screenWrapping, float deathTime):
	CharacterMariolandEnemy(renderer, imagePath, startPosition, map, moveSpeed, frameDelay, noOfFrames, animating, startFrame,
		currentNumOfFrames, initialJumpForce, gravity, jumpForceDecrement, collisionRadius, false, deathTime)
{
	mHitSound = new SoundEffect();
	mHitSound->Load("SFX/Marioland SFX/stomp.wav");

	mExplodeSound = new SoundEffect();
	mExplodeSound->Load("SFX/Marioland SFX/koopaExplode.wav");
	explosionSoundPlayed = false;

	mMovingLeft = true;

	mPercentageDead = 0.0f;
}

CharacterMariolandKoopa::~CharacterMariolandKoopa()
{
	delete mExplodeSound;
}

void CharacterMariolandKoopa::OnPlayerCollision(CharacterPlayable* player)
{
	CharacterMariolandEnemy::OnPlayerCollision(player);

	if (mPercentageDead >= 0.75f)
		player->KillPlayer();
}
