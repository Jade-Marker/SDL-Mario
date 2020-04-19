#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameScreenIntro.h"
#include "GameScreenGameover.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen) :
	mRenderer(renderer), mCurrentScreen(NULL), bkgMusic()
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
	if (firstUpdate)
	{
		mCurrentScreen->Update(deltaTime, e);
	}
	else
		firstUpdate = true;
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
		tempScreen = (GameScreen*)new GameScreenLevel1(mRenderer, this);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		bkgMusic.Load("Music/Mario.ogg");
		bkgMusic.Play(-1);
		firstUpdate = false;
		break;

	case SCREEN_LEVEL2:
		tempScreen = (GameScreen*)new GameScreenLevel2(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		bkgMusic.Load("Music/Marioland.ogg");
		bkgMusic.Play(-1);
		firstUpdate = false;
		break;

	case SCREEN_GAMEOVER:
		tempScreen = (GameScreen*)new GameScreenGameOver(mRenderer, this);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		break;
	}
}
