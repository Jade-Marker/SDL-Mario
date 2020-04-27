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
#include "ScoreManager.h"
#include "SoundList.h"
#include "EnemyWave.h"
#include "CharacterCrab.h"

#include <vector>

class Texture2D;
class PowBlock;

class GameScreenLevel1 : GameScreen
{
private:
	CharacterPlayable* mMarioCharacter;
	CharacterPlayable* mLuigiCharacter;
	LevelMap* mLevelMap;
	PowBlock* mPowBlock;

	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;

	std::vector<CharacterEnemy*> mEnemiesAndCoins;

	Font* scoreFont;

	GameScreenManager* mManager;

	std::vector<EnemyWave> mEnemyWaves;
	int mCurrentWave;

public:
	GameScreenLevel1(SDL_Renderer* renderer, GameScreenManager* manager);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	void HandleEnemyWave(float deltaTime);
	bool SetUpLevel();
	void SetLevelMap();
	void SetUpEnemyWaves();
	void UpdatePOWBlock();
	void DoScreenshake();
	void UpdateEnemiesAndCoins(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateCoin(Vector2D position, FACING direction, float speed);
	void CreateCrab(Vector2D position, FACING direction, float speed);
};

