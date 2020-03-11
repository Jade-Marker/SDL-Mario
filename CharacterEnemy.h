#pragma once
#include "Character.h"
class CharacterEnemy :
	public Character
{
protected:
	bool mAlive;

public:
	CharacterEnemy(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, float moveSpeed, float frameDelay, int noOfFrames, bool animating);
	virtual ~CharacterEnemy();

	virtual void TakeDamage();
	void SetAlive(bool value);
	bool GetAlive();

};

