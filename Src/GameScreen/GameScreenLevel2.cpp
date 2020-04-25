#include "GameScreenLevel2.h"

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer, GameScreenManager* manager):
	GameScreen(renderer), mRenderer(renderer), mManager(manager), mBackToMenu(false)
{
	SetUpLevel();

	mMario = new CharacterMario(mRenderer, "Images/Marioland images/Mario.png", MARIOLAND_INIT_POS, SDLK_w, SDLK_d, SDLK_a,
		mLevelMap, MARIOLAND_MOVESPEED, nullptr, "Mario", MARIO_TEXT_POS, MARIOLAND_INITIAL_LIVES, LEVEL2_PLAYER_FRAME_DELAY,
		MARIO_IDLE_FRAME_COUNT, MARIOLAND_FRAME_COUNT, MARIO_IDLE_START_FRAME, MARIOLAND_JUMP_FRAME_COUNT, MARIOLAND_JUMP_START_FRAME, MARIOLAND_MOVE_FRAME_COUNT, MARIOLAND_MOVE_START_FRAME,
		MARIO_IDLE_FRAME_COUNT, MARIO_IDLE_START_FRAME,	MARIOLAND_JUMP_FORCE, MARIOLAND_GRAVITY, MARIOLAND_JUMP_DECREMENT, MARIOLAND_COLLISION_RADIUS, "SFX/Marioland SFX/jump.wav", this, false);

	SpawnEnemies();

	scoreFont = new Font(renderer, "Fonts/Press Start 2P black.png", 32, 32, ' ');
}

GameScreenLevel2::~GameScreenLevel2()
{
	delete mLevelMap;
	delete mMario;
	delete scoreFont;

	for (int i = 0; i < mEnemiesAndCoins.size(); i++)
	{
		delete mEnemiesAndCoins[i];
	}
	mEnemiesAndCoins.clear();
}

void GameScreenLevel2::SetUpLevel()
{
	if (!mLevelMap)
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
						mLevelMap, FACING_RIGHT, 0.0f, 0.0f, 0.0f, 0.0f, MARIOLAND_COLLISION_RADIUS, 0.0f, MARIOLAND_COIN_FRAME_COUNT, "SFX/Marioland SFX/coin.wav", false);
					mEnemiesAndCoins.push_back(coin);

				}
			}
		}
	}else if (mEnemiesAndCoins.size() > 0)
	{
		for (int i = 0; i < mEnemiesAndCoins.size(); i++)
		{
			//deletes all objects in mEnemiesAndCoins that aren't coins
			CharacterCoin* enemy = dynamic_cast<CharacterCoin*>(mEnemiesAndCoins[i]);
			if (!enemy)
			{
				delete mEnemiesAndCoins[i];
				mEnemiesAndCoins.erase(mEnemiesAndCoins.begin() + i);
				i--;
			}
		}
	}
}

void GameScreenLevel2::SpawnEnemies()
{
	CreateGoomba(Vector2D(284.0f, 208.0f));
	CreateGoomba(Vector2D(1018.0f, 160.0f));
	CreateGoomba(Vector2D(1264.0f, 96.0f));
	CreateGoomba(Vector2D(1306.0f, 64.0f));
	CreateGoomba(Vector2D(2796.0f, 160.0f));
	CreateGoomba(Vector2D(2940.0f, 160.0f));
	CreateGoomba(Vector2D(3304.0f, 208.0f));
	CreateGoomba(Vector2D(3354.0f, 208.0f));

	CreateFly(Vector2D(2594.0f, 190.0f));
	CreateFly(Vector2D(3720.0f, 190.0f));
	CreateFly(Vector2D(3912.0f, 190.0f));

	CreateKoopa(Vector2D(1804.0f, 190.0f));
}

void GameScreenLevel2::Render()
{
	mLevelMap->Render(0.0f, -xOffset);

	for (unsigned int i = 0; i < mEnemiesAndCoins.size(); i++)
	{
		mEnemiesAndCoins[i]->Render(-xOffset);
	}

	mMario->Render(-xOffset);

	mMario->RenderScoreAndLives(scoreFont);
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	UpdateEnemiesAndCoins(deltaTime, e);

	mMario->Update(deltaTime, e);
	float marioXpos = mMario->GetPosition().x;

	if (marioXpos > SCREEN_WIDTH / 2.0f)
	{
		xOffset = marioXpos - SCREEN_WIDTH / 2.0f;
	}

	if (marioXpos >= MARIOLAND_END_POS)
		mBackToMenu = true;

	if (xOffset < 0)
		xOffset = 0;

	if (xOffset > mLevelMap->GetTileset().tileWidth * (mLevelMap->GetWidth()- (float)SCREEN_WIDTH/mLevelMap->GetTileset().tileWidth))
		xOffset = mLevelMap->GetTileset().tileWidth * (mLevelMap->GetWidth() - (float)SCREEN_WIDTH / mLevelMap->GetTileset().tileWidth);

	if (mBackToMenu)
		mManager->ChangeScreen(SCREEN_INTRO);
}

void GameScreenLevel2::CreateGoomba(Vector2D position)
{
	CharacterEnemy* enemy = new CharacterGoomba(mRenderer, "Images/Marioland images/Goomba.png", position, mLevelMap, MARIOLAND_GOOMBA_SPEED, ANIMATION_DELAY,
		MARIOLAND_GOOMBA_FRAME_COUNT, true, MARIOLAND_GOOMBA_START_FRAME, MARIOLAND_GOOMBA_WALK_FRAME_COUNT,
		INITIAL_JUMP_FORCE_SMALL, MARIOLAND_GRAVITY, MARIOLAND_JUMP_DECREMENT, MARIOLAND_COLLISION_RADIUS, false, MARIOLAND_GOOMBA_SCORE);
	mEnemiesAndCoins.push_back(enemy);
}

void GameScreenLevel2::CreateFly(Vector2D position)
{
	CharacterEnemy* enemy = new CharacterFly(mRenderer, "Images/Marioland images/Fly.png", position, mLevelMap, MARIOLAND_FLY_SPEED, ANIMATION_DELAY,
		MARIOLAND_FLY_FRAME_COUNT, true, MARIOLAND_FLY_START_FRAME, MARIOLAND_FLY_WALK_FRAME_COUNT,
		MARIOLAND_FLY_JUMP_FORCE, MARIOLAND_GRAVITY, MARIOLAND_JUMP_DECREMENT, MARIOLAND_FLY_COLLISION_RADIUS, mMario, MARIOLAND_FLY_SCORE);
	mEnemiesAndCoins.push_back(enemy);
}

void GameScreenLevel2::CreateKoopa(Vector2D position)
{
	CharacterEnemy* enemy = new CharacterMariolandKoopa(mRenderer, "Images/Marioland images/Koopa.png", position, mLevelMap, MARIOLAND_GOOMBA_SPEED, ANIMATION_DELAY,
		MARIOLAND_KOOPA_FRAME_COUNT, true, MARIOLAND_KOOPA_START_FRAME, MARIOLAND_KOOPA_WALK_FRAME_COUNT,
		MARIOLAND_FLY_JUMP_FORCE, MARIOLAND_GRAVITY, MARIOLAND_JUMP_DECREMENT, MARIOLAND_KOOPA_COLLISION_RADIUS, MARIOLAND_KOOPA_SCORE, false, MARIOLAND_KOOPA_DEATH_TIME);
	mEnemiesAndCoins.push_back(enemy);
}

void GameScreenLevel2::CreateQMarkCoin(Vector2D position)
{
	CharacterEnemy* enemy = new CharacterQMarkCoin(mRenderer, "Images/Marioland images/Coin.png", position, mLevelMap, MARIOLAND_COIN_SPEED, ANIMATION_DELAY,
		MARIOLAND_COIN_FRAME_COUNT, false, MARIOLAND_COIN_START_FRAME, MARIOLAND_COIN_FRAME_COUNT, 0.0f, 0.0f, MARIOLAND_COLLISION_RADIUS, MARIOLAND_COIN_ALIVE_TIME, mMario);
	mEnemiesAndCoins.push_back(enemy);
}

void GameScreenLevel2::RestartLevel()
{
	if (mMario->GetLives() >= 0)
	{
		SetUpLevel();
		SpawnEnemies();

		mMario->SetPosition(MARIOLAND_INIT_POS);
		xOffset = 0.0f;
	}
	else
		mBackToMenu = true;
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

				if (Collisions::Instance()->Circle(mMario->GetCollisionCircle(), mEnemiesAndCoins[i]->GetCollisionCircle()) && mMario->GetState() != DEAD)
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
