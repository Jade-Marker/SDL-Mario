#pragma once
#include "Character.h"
#include "Texture2D.h"
class CharacterPlayable :
	public Character
{
private:
	std::map<INPUT_TYPE, int> mInputMap;
	CHARACTERSTATE state;

public:
	CharacterPlayable(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, int jumpKey, int rightKey, int leftKey, LevelMap* map, float moveSpeed);
	virtual void Render();
	void Update(float deltaTime, SDL_Event e);
	void SetState(CHARACTERSTATE newState);
	CHARACTERSTATE GetState();
};

