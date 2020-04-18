#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, int jumpKey, int rightKey, int leftKey,
    LevelMap* map, float moveSpeed, std::vector<CharacterEnemy*>* const enemiesList, std::string name, float scoreXPos, int initialLives,
    float frameDelay, int initalNumOfFrames, int totalNumOfFrames, int startingFrame,
    int jumpFrameCount, int jumpStartFrame, int moveFrameCount, int moveStartFrame, int idleFrameCount, int idleStartFrame,
	float initialJumpForce, float gravity, float jumpForceDecrement, bool screenWrappingEnabled):
    CharacterPlayable(renderer, imagePath, startPosition, jumpKey, rightKey, leftKey,
        map, moveSpeed, enemiesList, name, scoreXPos, initialLives,
        frameDelay, initalNumOfFrames, totalNumOfFrames, startingFrame,
        jumpFrameCount, jumpStartFrame, moveFrameCount, moveStartFrame, idleFrameCount, idleStartFrame,
		initialJumpForce, gravity, jumpForceDecrement,screenWrappingEnabled)
{
}

void CharacterMario::UpdateState()
{
	if (mJumping || !mCanJump)
	{
		mState = JUMPING;
	}
	else if (mMovingLeft || mMovingRight)
	{
		mState = MOVING;
	}
	else
	{
		mState = IDLE;
	}
}
