#include "GameScreenGameOver.h"
#include <iostream>
#include "Texture2D.h"

GameScreenGameOver::GameScreenGameOver(SDL_Renderer* renderer, GameScreenManager* manager):
	GameScreen(renderer),
	mManager(manager)
{
	SetUpLevel();

	highScoreText = new Font(renderer, "Fonts/Press Start 2P.png", 32, 32, ' ');
}

GameScreenGameOver::~GameScreenGameOver()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
}

void GameScreenGameOver::Render()
{
	//Draw the background
	//mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
	highScoreText->DrawString("You got " + std::to_string(5) + " points", Vector2D(0, 0), Vector2D(1, 1));
}

void GameScreenGameOver::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	}
}

bool GameScreenGameOver::SetUpLevel()
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
