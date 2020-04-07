#pragma once

#include <vector>
#include "Commons.h"

struct WaveComponent 
{
	ENEMIES enemy;
	float spawnDelay;
	Vector2D position;
	FACING direction;
	float speed;
	bool spawned;

	WaveComponent(ENEMIES enemyInput, float spawnDelayInput, Vector2D positionInput, FACING directionInput, float speedInput) :
		enemy(enemyInput), spawnDelay(spawnDelayInput), position(positionInput), direction(directionInput), speed(speedInput), spawned(false)
	{};
};

class EnemyWave
{
private:
	std::vector<WaveComponent> mWave;

public:
	EnemyWave(std::vector<WaveComponent>& wave);
	EnemyWave();
	void SetWave(std::vector<WaveComponent>& wave);
	const std::vector<WaveComponent>& GetWave();
};

