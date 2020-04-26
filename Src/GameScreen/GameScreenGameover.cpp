#include "GameScreenGameOver.h"
#include <iostream>
#include "Texture2D.h"

GameScreenGameOver::GameScreenGameOver(SDL_Renderer* renderer, GameScreenManager* manager):
	GameScreen(renderer), mManager(manager), mGotPlayerName(false)
{
	SetUpLevel();

	mHighScoreText = new Font(renderer, "Fonts/Press Start 2P.png", 32, 32, ' '); 
	mBackgroundTexture = new Texture2D(mRenderer);
	mBackgroundTexture->LoadFromFile("Images/gameOver.png");
}

GameScreenGameOver::~GameScreenGameOver()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete mHighScoreText;
}

void GameScreenGameOver::Render()
{
	mBackgroundTexture->Render(Vector2D(0.0f, 0.0f), SDL_FLIP_NONE);

	if (mGotPlayerName) {
		std::string scoreString = std::to_string(ScoreManager::Instance()->GetPlayerScore());
		int numOfHighscores;
		Score* highscoreTable = ScoreManager::Instance()->GetHighscoreTable(numOfHighscores);

		mHighScoreText->DrawString("You got " + scoreString + " points", HIGHSCORE_YOU_GOT_POS, HIGHSCORE_YOU_GOT_SCALE);

		mHighScoreText->DrawString("Highscores:", Vector2D(HIGHSCORE_HIGHSCORE_POS_X, HIGHSCORE_HIGHSCORE_POS_Y), HIGHSCORE_HIGHSCORE_SCALE);
		for (int i = 0; i < numOfHighscores; i++)
		{
			mHighScoreText->DrawString(highscoreTable[i].name + ":" + std::to_string(highscoreTable[i].score),
				Vector2D(HIGHSCORE_HIGHSCORE_POS_X, HIGHSCORE_HIGHSCORE_VALUE_POS_Y + HIGHSCORE_HIGHSCORE_VALUE_INCREMENT_POS_Y * i), HIGHSCORE_HIGHSCORE_SCALE);
		}
	}
	else
	{
		mHighScoreText->DrawString("Please enter your name ", HIGHSCORE_ENTER_NAME_POS, HIGHSCORE_ENTER_NAME_SCALE);
		mHighScoreText->DrawString(mPlayerName, HIGHSCORE_ENTER_NAME_NAME_POS, HIGHSCORE_ENTER_NAME_NAME_SCALE);
	}
}

void GameScreenGameOver::Update(float deltaTime, SDL_Event e)
{
	if (!mGotPlayerName)
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			if (e.key.keysym.sym == SDLK_RETURN)
			{
				mGotPlayerName = true;
				ScoreManager::Instance()->UpdateHighscoreTable(mPlayerName);
			}
			else if (e.key.keysym.sym == SDLK_BACKSPACE && mPlayerName.length() > 0)
			{
				mPlayerName.erase(mPlayerName.length() - 1);
			}
			else if (mPlayerName.length() < NAME_MAX_LENGTH)
			{
				int currentKey = e.key.keysym.sym;
				if (currentKey >= SDLK_a && currentKey <= SDLK_z)
					//SDLK_a lines up with ascii 'a', so subtract ('a'- 'A') to force all characters to be uppercase
					mPlayerName += (char)e.key.keysym.sym - ('a' - 'A');

				else if (currentKey == SDLK_SPACE)
					mPlayerName += ' ';

				else if (currentKey >= SDLK_0 && currentKey <= SDLK_9)
					mPlayerName += (char)e.key.keysym.sym;
			}
		}
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
