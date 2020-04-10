#pragma once

#include <string>
#include <fstream>
#include "Constants.h"
#include "Commons.h"

struct Score 
{
	std::string name;
	int score;
};

class ScoreManager
{
private:
	static ScoreManager* mInstance;
	int mPlayerScore;
	std::string mPlayerName;

	Score mHighScores[HIGHSCORE_COUNT];
	int mNumOfScores;
	bool mNewHighScore;
	int mNewScoreIndex;

	ScoreManager();

public:
	~ScoreManager();
	static ScoreManager* Instance();

	void SetPlayerScore(int score);
	int GetPlayerScore();
	void UpdateHighscoreTable(std::string playerName);
	Score* GetHighscoreTable(int& numOfScores);
};

