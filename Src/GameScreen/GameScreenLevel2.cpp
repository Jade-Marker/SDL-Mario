#include "GameScreenLevel2.h"

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer):
	GameScreen(renderer), mRenderer(renderer)
{
	std::vector<TILE> passableTiles;

	std::vector<TILE> impassableTiles;
	impassableTiles.push_back((TILE)0x13);
	impassableTiles.push_back((TILE)0x21);
	impassableTiles.push_back((TILE)0x24);
	impassableTiles.push_back((TILE)0x39);
	impassableTiles.push_back((TILE)0x60);
	impassableTiles.push_back((TILE)0x61);
	impassableTiles.push_back((TILE)0x63);
	impassableTiles.push_back((TILE)0x70);
	impassableTiles.push_back((TILE)0x71);
	impassableTiles.push_back((TILE)0x72);
	impassableTiles.push_back((TILE)0x73);
	impassableTiles.push_back((TILE)0x7f);
	impassableTiles.push_back((TILE)0x80);
	impassableTiles.push_back((TILE)0x81);
	impassableTiles.push_back((TILE)0x82);
	impassableTiles.push_back((TILE)0x8e);
	impassableTiles.push_back((TILE)0x8f);
	impassableTiles.push_back((TILE)0xe8);

	for (int i = 0; i < 255; i++)
	{
		bool passable = true;

		for (int j = 0; j < impassableTiles.size(); j++)
		{
			if (impassableTiles[j] == i)
				passable = false;
		}

		if (passable)
			passableTiles.push_back((TILE)i);
	}

	mLevelMap = new LevelMap(mRenderer, "Images/Marioland images/tileset.png", 16, 16, false, passableTiles, "Levels/Level2.txt");
	xOffset = 0.0f;
	mMario = new CharacterMario(mRenderer, "Images/Marioland images/Mario.png", Vector2D(0.0f, 0.0f), SDLK_w, SDLK_d, SDLK_a,
		mLevelMap, 100.0f, nullptr, "Mario", 0.0f, INITIAL_LIVES, LEVEL2_PLAYER_FRAME_DELAY, 1, 5, 0, 1, 4, 3, 1, 1, 0,
		INITIAL_JUMP_FORCE, GRAVITY, JUMP_FORCE_DECREMENT, false);
}

GameScreenLevel2::~GameScreenLevel2()
{
}

void GameScreenLevel2::Render()
{
	mLevelMap->Render(0.0f, -xOffset);
	mMario->Render(-xOffset);
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	float oldXPos = mMario->GetPosition().x;
	mMario->Update(deltaTime, e);
	float newXPos = mMario->GetPosition().x;

	if (newXPos > SCREEN_WIDTH / 2.0f)
	{
		xOffset += newXPos - oldXPos;
	}


	if (xOffset < 0)
	{
		xOffset = 0;
	}

	if (xOffset > mLevelMap->GetTileset().tileWidth * (mLevelMap->GetWidth()- (float)SCREEN_WIDTH/mLevelMap->GetTileset().tileWidth))
	{
		xOffset = mLevelMap->GetTileset().tileWidth * (mLevelMap->GetWidth() - (float)SCREEN_WIDTH / mLevelMap->GetTileset().tileWidth);
	}
}
