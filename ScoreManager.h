#pragma once
class ScoreManager
{
private:
	static ScoreManager* mInstance;
	int playerScore;

	ScoreManager();

public:
	~ScoreManager();
	static ScoreManager* Instance();

	void SetPlayerScore(int score);
	int GetPlayerScore();
};

