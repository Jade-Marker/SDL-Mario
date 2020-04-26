#pragma once

#include "GameScreen.h"
#include "LevelMap.h"
#include "CharacterMario.h"
#include "CharacterEnemy.h"
#include "CharacterCoin.h"
#include "CharacterGoomba.h"
#include "CharacterFly.h"
#include "CharacterMariolandKoopa.h"
#include "CharacterQMarkCoin.h"
#include "GameScreenManager.h"

class GameScreenLevel2: GameScreen
{
protected:
	SDL_Renderer* mRenderer;
	LevelMap* mLevelMap;
	float xOffset;
	CharacterPlayable* mMario;
	std::vector<CharacterEnemy*> mEnemiesAndCoins;
	Font* scoreFont;

	GameScreenManager* mManager;
	bool mBackToMenu;

public:
	GameScreenLevel2(SDL_Renderer* renderer, GameScreenManager* manager);
	virtual ~GameScreenLevel2();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void CreateGoomba(Vector2D position);
	void CreateFly(Vector2D position);
	void CreateKoopa(Vector2D position);
	void CreateQMarkCoin(Vector2D position);

	void RestartLevel();

private:
	void SetUpLevel();
	void SpawnEnemies();
	void UpdateEnemiesAndCoins(float deltaTime, SDL_Event e);
};

