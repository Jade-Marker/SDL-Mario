#include "ScoreManager.h"

ScoreManager* ScoreManager::mInstance = nullptr;

ScoreManager::ScoreManager():
	mPlayerScore(0), mNewHighScore(false)
{
	std::ifstream inFile(HIGHSCORE_FILE_PATH);

	//initialise the array
	for (int i = 0; i < HIGHSCORE_COUNT; i++)
	{
		mHighScores[i].name = "";
		mHighScores[i].score = 0;
	}

	inFile.seekg(0, std::ios::end);
	//if tellg == 0, then the file is emtpy
	if (inFile.tellg() != 0) {
		inFile.seekg(std::ios::beg);

		inFile >> mNumOfScores;
		for (int i = 0; i < mNumOfScores; i++)
		{
			inFile >> mHighScores[i].name;
			inFile >> mHighScores[i].score;
		}
		inFile.close();

	}
	else
		mNumOfScores = 0;
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
	mPlayerScore = score;

	mNewHighScore = false;
	for (int i = 0; i < HIGHSCORE_COUNT; i++)
	{
		if (mPlayerScore > mHighScores[i].score)
		{
			mNewHighScore = true;
			mNewScoreIndex = i;
			break;
		}
	}
}

int ScoreManager::GetPlayerScore()
{
	return mPlayerScore;
}

void ScoreManager::UpdateHighscoreTable(std::string playerName)
{
	mPlayerName = playerName;

	if (mNewHighScore)
	{
		//adding a new score, so increment the count
		if (mNumOfScores < HIGHSCORE_COUNT)
			mNumOfScores++;

		//moves all scores beneath new score down one
		for (int i = mNumOfScores - 1; i > mNewScoreIndex; i--)
		{
			mHighScores[i] = mHighScores[i - 1];
		}

		mHighScores[mNewScoreIndex].name = mPlayerName;
		mHighScores[mNewScoreIndex].score = mPlayerScore;

		//rewrite highscore table
		std::ofstream outFile(HIGHSCORE_FILE_PATH);
		outFile << mNumOfScores << std::endl;
		for (int i = 0; i < mNumOfScores; i++)
		{
			outFile << mHighScores[i].name << std::endl;
			outFile << mHighScores[i].score << std::endl;
		}
		outFile.close();
	}
}

Score* ScoreManager::GetHighscoreTable(int& numOfScores)
{
	numOfScores = mNumOfScores;
	return mHighScores;
}
