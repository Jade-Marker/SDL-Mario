#include "ScoreManager.h"

ScoreManager* ScoreManager::mInstance = nullptr;

ScoreManager::ScoreManager():
	playerScore(0)
{
}

ScoreManager::~ScoreManager()
{
	mInstance = nullptr;
}

ScoreManager* ScoreManager::Instance()
{
	if (!mInstance)
		mInstance = new ScoreManager();

	return mInstance;
}

void ScoreManager::SetPlayerScore(int score)
{
	playerScore = score;
}

int ScoreManager::GetPlayerScore()
{
	return playerScore;
}
