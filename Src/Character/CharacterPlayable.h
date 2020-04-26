#pragma once
#include "Character.h"
#include "CharacterEnemy.h"
#include "Texture2D.h"
#include "Font.h"

#include <vector>

class CharacterPlayable :
	public Character
{
protected:
	std::map<INPUT_TYPE, int> mInputMap;
	CHARACTERSTATE mState;
	int mScore;
	std::vector<CharacterEnemy*>* mEnemiesList;
	std::string mName;
	float mScoreXPos;
	int mLives;

	bool mInvulnerable;
	float mInvulnTimer;

	const int JUMP_FRAME_COUNT;
	const int JUMP_START_FRAME;
	const int MOVE_FRAME_COUNT;
	const int MOVE_START_FRAME;
	const int IDLE_FRAME_COUNT;
	const int IDLE_START_FRAME;

public:
	CharacterPlayable(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, int jumpKey, int rightKey, int leftKey,
		LevelMap* map, float moveSpeed, std::vector<CharacterEnemy*>* const enemiesList, std::string name, float scoreXPos, int initialLives,
		float frameDelay, int initalNumOfFrames, int totalNumOfFrames, int startingFrame,
		int jumpFrameCount, int jumpStartFrame, int moveFrameCount, int moveStartFrame, int idleFrameCount,
		int idleStartFrame, float initialJumpForce, float gravity, float jumpForceDecrement, float collisionRadius,
		std::string jumpSFXPath, bool screenWrappingEnabled = true);
	virtual void Render(float xOffset = 0.0f);
	virtual void Update(float deltaTime, SDL_Event e);
	virtual void OnPlayerCollision(CharacterPlayable* player);
	void SetState(CHARACTERSTATE newState);
	CHARACTERSTATE GetState();
	virtual void KillPlayer();
	void IncrementScore(int value);
	int GetScore();
	void RenderScoreAndLives(Font* font);
	void JumpedOnEnemy();
	int GetLives() { return mLives; };

protected:
	virtual void UpdateState();
	void Animate();
	void HitTile();

};

