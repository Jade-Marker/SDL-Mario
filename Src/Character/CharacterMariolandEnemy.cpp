#include "CharacterMariolandEnemy.h"

void CharacterMariolandEnemy::AliveUpdate(float deltaTime, SDL_Event e)
{
    int leftX = (int)(roundf(mPosition.x) / mCurrentLevelMap->GetTileset().tileWidth);
    int rightX = (int)(roundf(mPosition.x + mSingleSpriteWidth) / mCurrentLevelMap->GetTileset().tileWidth);
    int y = (int)(mPosition.y / mCurrentLevelMap->GetTileset().tileHeight);

    if (mMovingLeft)
    {
        if (!mCurrentLevelMap->TileIsPassable(mCurrentLevelMap->GetTileAt(y, leftX)))
        {
            mMovingLeft = false;
            mMovingRight = true;
        }
    }
    else if (mMovingRight)
    {
        if (!mCurrentLevelMap->TileIsPassable(mCurrentLevelMap->GetTileAt(y, rightX)))
        {
            mMovingLeft = true;
            mMovingRight = false;
        }
    }
}

void CharacterMariolandEnemy::DeadUpdate(float deltaTime, SDL_Event e)
{
    mDeathTimer += deltaTime;
    if (mDeathTimer >= DEATH_TIME)
        mAlive = false;
}

CharacterMariolandEnemy::CharacterMariolandEnemy(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map,
    float moveSpeed, float frameDelay, int noOfFrames, bool animating, int startFrame, int currentNumOfFrames, float initialJumpForce,
    float gravity, float jumpForceDecrement, float collisionRadius, bool screenWrapping, float deathTime, int scoreWorth):
    CharacterEnemy(renderer, imagePath, startPosition, map, moveSpeed, frameDelay, noOfFrames, animating, startFrame,
        currentNumOfFrames, initialJumpForce, gravity, jumpForceDecrement, collisionRadius, false), DEATH_TIME(deathTime), mState(MOVING), mScoreWorth(scoreWorth)
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
        player->IncrementScore(mScoreWorth);

        if(mHitSound)
            mHitSound->Play(0);
    }
    else if (mState != DEAD)
        player->KillPlayer();
}
