#include "CharacterEnemy.h"

CharacterEnemy::CharacterEnemy(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float moveSpeed):
	Character(renderer, imagePath, startPosition, map, moveSpeed)
{
}

CharacterEnemy::~CharacterEnemy()
{
}

void CharacterEnemy::TakeDamage()
{
}

void CharacterEnemy::SetAlive(bool value)
{
	mAlive = value;
}

bool CharacterEnemy::GetAlive()
{
	return mAlive;
}
