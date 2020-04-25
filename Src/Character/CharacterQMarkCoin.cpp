#include "CharacterQMarkCoin.h"

CharacterQMarkCoin::CharacterQMarkCoin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map,
    float moveSpeed, float frameDelay, int noOfFrames, bool animating, int startFrame, int currentNumOfFrames,
    float initialJumpForce, float jumpForceDecrement, float collisionRadius, float aliveTime, CharacterPlayable* player):
    CharacterEnemy(renderer, imagePath, startPosition, map, moveSpeed,
        frameDelay, noOfFrames, animating, startFrame, currentNumOfFrames,
        initialJumpForce, 0.0f, jumpForceDecrement, collisionRadius, false), mAliveTimer(aliveTime)
{
    mCollectSound = new SoundEffect();
    mCollectSound->Load("SFX/Marioland SFX/coin.wav");
    mCollectSound->Play(0);

    player->IncrementScore(COIN_SCORE);
}

CharacterQMarkCoin::~CharacterQMarkCoin()
{
    delete mCollectSound;
}

void CharacterQMarkCoin::Update(float deltaTime, SDL_Event e)
{
    if (mAliveTimer > 0.0f)
    {
        mPosition.y -= cMovementSpeed * deltaTime;

        mAliveTimer -= deltaTime;

    }
    else if(!mCollectSound->Playing())
        mAlive = false;

    Character::Update(deltaTime, e);
}
