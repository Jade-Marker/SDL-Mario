#include "CharacterMariolandEnemy.h"

void CharacterMariolandEnemy::AliveUpdate(float deltaTime, SDL_Event e)
{
}

void CharacterMariolandEnemy::DeadUpdate(float deltaTime, SDL_Event e)
{
    mDeathTimer += deltaTime;
    if (mDeathTimer > DEATH_TIME)
        mAlive = false;
}

CharacterMariolandEnemy::CharacterMariolandEnemy(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map,
    float moveSpeed, float frameDelay, int noOfFrames, bool animating, int startFrame, int currentNumOfFrames, float initialJumpForce,
    float gravity, float jumpForceDecrement, float collisionRadius, bool screenWrapping, float deathTime):
    CharacterEnemy(renderer, imagePath, startPosition, map, moveSpeed, frameDelay, noOfFrames, animating, startFrame,
        currentNumOfFrames, initialJumpForce, gravity, jumpForceDecrement, collisionRadius, false), DEATH_TIME(deathTime)
{
}

CharacterMariolandEnemy::~CharacterMariolandEnemy()
{
    if (mHitSound)
        delete mHitSound;
}

void CharacterMariolandEnemy::Update(float deltaTime, SDL_Event e)
{
    if (mState == DEAD)
        DeadUpdate(deltaTime, e);
    else
        AliveUpdate(deltaTime, e);

    Character::Update(deltaTime, e);
}

void CharacterMariolandEnemy::OnPlayerCollision(CharacterPlayable* player)
{
    if (player->GetPosition().y + player->GetHeight() * MARIOLAND_ENEMY_HIT_PLAYER_HEIGHT_PROPORTION < mPosition.y && !player->CanJump() && mState != DEAD)
    {
        mState = DEAD;
        mMovingLeft = false;
        mMovingRight = false;
        player->JumpedOnEnemy();

        if(mHitSound)
            mHitSound->Play(0);
    }
    else if (mState != DEAD)
        player->KillPlayer();
}
