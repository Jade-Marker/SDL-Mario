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

	xOffset = 0.0f;
	mLevelMap = new LevelMap(mRenderer, "Images/Marioland images/tileset.png", 16, 16, false, passableTiles, "Levels/Level2.txt");

	for (int y = 0; y < mLevelMap->GetHeight(); y++)
	{
		for (int x = 0; x < mLevelMap->GetWidth(); x++)
		{
			if (mLevelMap->GetTileAt(y, x) == 0xf4)
			{
				mLevelMap->ChangeTileAt(y, x, (TILE)0x2c);

				CharacterEnemy* coin = new CharacterCoin(mRenderer, "Images/Marioland images/Coin.png", Vector2D(x * mLevelMap->GetTileset().tileWidth, y * mLevelMap->GetTileset().tileHeight),
					mLevelMap, FACING_RIGHT, 0.0f, 0.0f, 0.0f, 0.0f, MARIOLAND_COLLISION_RADIUS, 0.0f, 1, "SFX/Marioland SFX/coin.wav", false);
				mEnemiesAndCoins.push_back(coin);

			}
		}
	}

	mMario = new CharacterMario(mRenderer, "Images/Marioland images/Mario.png", Vector2D(0.0f, 0.0f), SDLK_w, SDLK_d, SDLK_a,
		mLevelMap, MARIOLAND_MOVESPEED, nullptr, "Mario", 0.0f, INITIAL_LIVES, LEVEL2_PLAYER_FRAME_DELAY,
		MARIO_IDLE_FRAME_COUNT, MARIOLAND_FRAME_COUNT, MARIO_IDLE_START_FRAME, MARIOLAND_JUMP_FRAME_COUNT, MARIOLAND_JUMP_START_FRAME, MARIOLAND_MOVE_FRAME_COUNT, MARIOLAND_MOVE_START_FRAME,
		MARIO_IDLE_FRAME_COUNT, MARIO_IDLE_START_FRAME,	MARIOLAND_JUMP_FORCE, MARIOLAND_GRAVITY, MARIOLAND_JUMP_DECREMENT, MARIOLAND_COLLISION_RADIUS, "SFX/Marioland SFX/jump.wav", false);

	CreateGoomba(Vector2D(284.0f, 208.0f));
	CreateGoomba(Vector2D(1018.0f, 160.0f));
	CreateGoomba(Vector2D(1264.0f, 96.0f));
	CreateGoomba(Vector2D(1306.0f, 64.0f));
	CreateGoomba(Vector2D(2796.0f, 160.0f));
	CreateGoomba(Vector2D(2940.0f, 160.0f));
	CreateGoomba(Vector2D(3304.0f, 208.0f));
	CreateGoomba(Vector2D(3354.0f, 208.0f));
}

GameScreenLevel2::~GameScreenLevel2()
{
}

void GameScreenLevel2::Render()
{
	mLevelMap->Render(0.0f, -xOffset);

	for (unsigned int i = 0; i < mEnemiesAndCoins.size(); i++)
	{
		mEnemiesAndCoins[i]->Render(-xOffset);
	}

	mMario->Render(-xOffset);
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	UpdateEnemiesAndCoins(deltaTime, e);

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

void GameScreenLevel2::CreateGoomba(Vector2D position)
{
	CharacterEnemy* enemy = new CharacterGoomba(mRenderer, "Images/Marioland images/Goomba.png", position, mLevelMap, MARIOLAND_GOOMBA_SPEED, ANIMATION_DELAY, 3, true, 0, 2,
		INITIAL_JUMP_FORCE_SMALL, MARIOLAND_GRAVITY, MARIOLAND_JUMP_DECREMENT, MARIOLAND_COLLISION_RADIUS, false);
	mEnemiesAndCoins.push_back(enemy);
}

void GameScreenLevel2::UpdateEnemiesAndCoins(float deltaTime, SDL_Event e)
{
	if (!mEnemiesAndCoins.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemiesAndCoins.size(); i++)
		{
			if (!(mEnemiesAndCoins[i]->GetPosition().x + mEnemiesAndCoins[i]->GetWidth() < xOffset || mEnemiesAndCoins[i]->GetPosition().x > xOffset + SCREEN_WIDTH))
			{

				//Now do the update
				mEnemiesAndCoins[i]->Update(deltaTime, e);

				if (Collisions::Instance()->Circle(mMario->GetCollisionCircle(), mEnemiesAndCoins[i]->GetCollisionCircle()) && mMario->GetState() != PLAYER_DEATH)
				{
					mEnemiesAndCoins[i]->OnPlayerCollision(mMario);
				}

				//If the enemy is no longer alive, then schedule it for deletion
				if (!mEnemiesAndCoins[i]->GetAlive())
					enemyIndexToDelete = i;
			}
		}

		if (enemyIndexToDelete != -1)
		{
			delete mEnemiesAndCoins[enemyIndexToDelete];
			mEnemiesAndCoins.erase(mEnemiesAndCoins.begin() + enemyIndexToDelete);
		}
	}
}
