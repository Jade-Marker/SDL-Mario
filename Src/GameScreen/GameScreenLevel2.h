#pragma once

#include "GameScreen.h"
#include "LevelMap.h"
#include "CharacterMario.h"
#include "CharacterEnemy.h"
#include "CharacterCoin.h"
#include "CharacterGoomba.h"

class GameScreenLevel2: GameScreen
{
protected:
	SDL_Renderer* mRenderer;
	LevelMap* mLevelMap;
	float xOffset;
	CharacterPlayable* mMario;
	std::vector<CharacterEnemy*> mEnemiesAndCoins;

public:
	GameScreenLevel2(SDL_Renderer* renderer);
	virtual ~GameScreenLevel2();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

private:
	void UpdateEnemiesAndCoins(float deltaTime, SDL_Event e);
};

