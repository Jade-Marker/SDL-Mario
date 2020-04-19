#pragma once

#include <SDL.h>
#include "Commons.h"
#include "SoundEffect.h"

class GameScreen;

class GameScreenManager
{
private:
	SDL_Renderer* mRenderer;
	GameScreen* mCurrentScreen;

	SoundEffect bkgMusic;
	bool firstUpdate;

public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS newScreen);
};

