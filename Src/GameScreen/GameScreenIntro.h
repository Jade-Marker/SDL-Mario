#pragma once

#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"
#include "GameScreenManager.h"

class Texture2D;

class GameScreenIntro : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	Texture2D* mArrow;
	int mArrowPosition;
	GameScreenManager* mManager;

public:
	GameScreenIntro(SDL_Renderer* renderer, GameScreenManager* manager);
	~GameScreenIntro();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	bool SetUpLevel();
};

