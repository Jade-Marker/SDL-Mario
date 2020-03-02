#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenIntro.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen) :
	mRenderer(renderer), mCurrentScreen(NULL)
{
	//Ensure the first screen is set up
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	mRenderer = NULL;
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);

	//Handle any events
	switch (e.type)
	{
	}
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	//Clear up the old screen
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;
	}

	GameScreen* tempScreen;

	switch (newScreen)
	{
	case SCREEN_INTRO:
		tempScreen = (GameScreen*)new GameScreenIntro(mRenderer, this);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		break;

	case SCREEN_LEVEL1:
		tempScreen = (GameScreen*)new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		break;
	}
}
