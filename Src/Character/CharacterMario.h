#pragma once
#include "CharacterPlayable.h"
class CharacterMario :
	public CharacterPlayable
{
public:
	CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, int jumpKey, int rightKey, int leftKey,
		LevelMap* map, float moveSpeed, std::vector<CharacterEnemy*>* const enemiesList, std::string name, float scoreXPos, int initialLives,
		float frameDelay, int initalNumOfFrames, int totalNumOfFrames, int startingFrame,
		int jumpFrameCount, int jumpStartFrame, int moveFrameCount, int moveStartFrame, int idleFrameCount, int idleStartFrame, bool screenWrappingEnabled = true);

	void UpdateState();
};

