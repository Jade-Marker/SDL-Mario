#pragma once
#include "Character.h"
#include "CharacterEnemy.h"
#include "Texture2D.h"
#include "Font.h"

#include <vector>

class CharacterPlayable :
	public Character
{
private:
	std::map<INPUT_TYPE, int> mInputMap;
	CHARACTERSTATE mState;
	int mScore;
	std::vector<CharacterEnemy*>* mEnemiesList;
	std::string mName;
	float mScoreXPos;
	int mLives;

	bool mInvulnerable;
	float mInvulnTimer;

public:
	CharacterPlayable(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, int jumpKey, int rightKey, int leftKey,
		LevelMap* map, float moveSpeed, std::vector<CharacterEnemy*>* const enemiesList, std::string name, float scoreXPos, int initialLives,
		float frameDelay, int initalNumOfFrames, int totalNumOfFrames, int startingFrame,
		bool screenWrappingEnabled = true);
	virtual void Render(float xOffset = 0.0f);
	void Update(float deltaTime, SDL_Event e);
	void Animate();
	virtual void OnPlayerCollision(CharacterPlayable* player);
	void SetState(CHARACTERSTATE newState);
	CHARACTERSTATE GetState();
	void KillPlayer();
	void IncrementScore(int value);
	int GetScore();
	void RenderScoreAndLives(Font* font);
	void UpdateState();

private:
	void HitTile();

};

