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

	if (mArrowPosition == 0)
		mArrow->Render(Vector2D(29, 61), SDL_FLIP_NONE);
	else
		mArrow->Render(Vector2D(29, 270), SDL_FLIP_NONE);
}

void GameScreenIntro::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		if (e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_UP)
		{
			mArrowPosition--;
			if (mArrowPosition < 0)
				mArrowPosition = 1;
		}

		if (e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_DOWN)
		{
			mArrowPosition++;
			if (mArrowPosition > 1)
				mArrowPosition = 0;
		}

		if (e.key.keysym.sym == SDLK_RETURN)
			mManager->ChangeScreen((SCREENS)(SCREEN_LEVEL1 + mArrowPosition));
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

	mArrow = new Texture2D(mRenderer);
	if (!mArrow->LoadFromFile("Images/arrow.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	mArrowPosition = 0;

	return true;
}
