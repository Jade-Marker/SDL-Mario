#include "EnemyWave.h"

EnemyWave::EnemyWave(std::vector<WaveComponent>& wave) :
	mWave(wave)
{
}

EnemyWave::EnemyWave()
{
}

void EnemyWave::SetWave(std::vector<WaveComponent>& wave)
{
	mWave = wave;
}

const std::vector<WaveComponent>& EnemyWave::GetWave()
{
	return mWave;
}
