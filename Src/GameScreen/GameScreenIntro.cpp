#include "GameScreenIntro.h"
#include <iostream>
#include "Texture2D.h"

GameScreenIntro::GameScreenIntro(SDL_Renderer* renderer, GameScreenManager* manager): 
	GameScreen(renderer),
	mManager(manager)
{
	SetUpLevel();
}

GameScreenIntro::~GameScreenIntro()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
}

void GameScreenIntro::Render()
{
	//Draw the background
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameScreenIntro::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		if (e.key.keysym.sym == SDLK_RETURN)
			mManager->ChangeScreen(SCREEN_LEVEL1);
	}
}

bool GameScreenIntro::SetUpLevel()
{
	//Load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/intro.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	return true;
}
