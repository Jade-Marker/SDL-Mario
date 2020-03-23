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
		LevelMap* map, float moveSpeed, std::vector<CharacterEnemy*>* const enemiesList, std::string name, float scoreXPos, int initialLives);
	virtual void Render();
	void Update(float deltaTime, SDL_Event e);
	virtual void OnPlayerCollision(CharacterPlayable* player);
	void SetState(CHARACTERSTATE newState);
	CHARACTERSTATE GetState();
	void KillPlayer();
	void IncrementScore(int value);
	void RenderScoreAndLives(Font* font);

private:
	void HitTile();

};

