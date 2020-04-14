#pragma once

#include "GameScreen.h"
#include "LevelMap.h"
#include "CharacterPlayable.h"

class GameScreenLevel2: GameScreen
{
protected:
	SDL_Renderer* mRenderer;
	LevelMap* mLevelMap;
	float xOffset;
	CharacterPlayable* mMario;

public:
	GameScreenLevel2(SDL_Renderer* renderer);
	virtual ~GameScreenLevel2();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
};

