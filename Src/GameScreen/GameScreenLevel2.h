#pragma once

#include "GameScreen.h"

class GameScreenLevel2: GameScreen
{
protected:
	SDL_Renderer* mRenderer;

public:
	GameScreenLevel2(SDL_Renderer* renderer);
	virtual ~GameScreenLevel2();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
};

