#pragma once

#include <SDL.h>
#include <string>
#include "Commons.h"
#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Font.h"
#include "ScoreManager.h"

class Texture2D;

class GameScreenGameOver : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	GameScreenManager* mManager;
	Font* highScoreText;

public:
	GameScreenGameOver(SDL_Renderer* renderer, GameScreenManager* manager);
	~GameScreenGameOver();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	bool SetUpLevel();
};

