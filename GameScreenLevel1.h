#pragma once

#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "LevelMap.h"
#include "CharacterPlayable.h"
#include "CharacterKoopa.h"
#include "CharacterCoin.h"
#include "Font.h"
#include "GameScreenManager.h"

#include <vector>

class Texture2D;
class PowBlock;

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	CharacterPlayable* mMarioCharacter;
	CharacterPlayable* mLuigiCharacter;
	LevelMap* mLevelMap;
	PowBlock* mPowBlock;

	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;

	std::vector<CharacterEnemy*> mEnemiesAndCoins;
	float mEnemySpawnTimer;
	float mCoinSpawnTimer;

	Font* scoreFont;

	GameScreenManager* mManager;

public:
	GameScreenLevel1(SDL_Renderer* renderer, GameScreenManager* manager);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	bool SetUpLevel();
	void SetLevelMap();
	void UpdatePOWBlock();
	void DoScreenshake();
	void UpdateEnemiesAndCoins(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateCoin(Vector2D position, FACING direction, float speed);
};

