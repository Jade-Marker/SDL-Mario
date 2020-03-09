#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"
#include "PowBlock.h"

//Todo
//Refactor character so that the code that handles frame stuff is in Character
//Implement another enemy (get sprite from here: https://www.spriters-resource.com/arcade/mariobros/sheet/93677/)


GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer), mLevelMap(NULL)
{
	SetLevelMap();
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete mMarioCharacter;
	mMarioCharacter = NULL;

	delete mLuigiCharacter;
	mLuigiCharacter = NULL;

	delete mPowBlock;
	mPowBlock = NULL;

	delete mLevelMap;
	mLevelMap = NULL;

	for (int i = 0; i < mEnemiesAndCoins.size(); i++)
		delete mEnemiesAndCoins[i];
	mEnemiesAndCoins.clear();
}

void GameScreenLevel1::Render()
{
	//Draw the background
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);

	//Draw the enemies
	for (unsigned int i = 0; i < mEnemiesAndCoins.size(); i++)
	{
		mEnemiesAndCoins[i]->Render();
	}

	//Draw the character
	mMarioCharacter->Render();
	mLuigiCharacter->Render();

	mPowBlock->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	if (mScreenshake)
	{
		mScreenshakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = 3.0f * sin(mWobble);

		//End the shake after the duration
		if (mScreenshakeTime <= 0.0f)
		{
			mScreenshake = false;
			mBackgroundYPos = 0.0f;
		}
	}

	enemySpawnTimer -= deltaTime;
	if (enemySpawnTimer <= 0.0f)
	{
		enemySpawnTimer = ENEMY_SPAWN_TIME;
		CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
	}

	coinSpawnTimer -= deltaTime;
	if (coinSpawnTimer <= 0.0f)
	{
		coinSpawnTimer = COIN_SPAWN_TIME;
		CreateCoin(Vector2D(150, 32), FACING_RIGHT, COIN_SPEED);
		CreateCoin(Vector2D(325, 32), FACING_LEFT, COIN_SPEED);
	}

	//Update enemies and coins
	UpdateEnemiesAndCoins(deltaTime, e);

	//Update the player
	mMarioCharacter->Update(deltaTime, e);
	mLuigiCharacter->Update(deltaTime, e);

	if (Collisions::Instance()->Circle(mMarioCharacter->GetCollisionCircle(), mLuigiCharacter->GetCollisionCircle()))
	{
		mMarioCharacter->OnPlayerCollision(mLuigiCharacter);
		mLuigiCharacter->OnPlayerCollision(mMarioCharacter);
	}

	UpdatePOWBlock();
}

bool GameScreenLevel1::SetUpLevel()
{
	//Load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	CreateKoopa(Vector2D(150,32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325,32), FACING_LEFT, KOOPA_SPEED);
	enemySpawnTimer = ENEMY_SPAWN_TIME;

	CreateCoin(Vector2D(150, 32), FACING_RIGHT, COIN_SPEED);
	CreateCoin(Vector2D(325, 32), FACING_LEFT, COIN_SPEED);
	coinSpawnTimer = COIN_SPAWN_TIME;
	
	//Set up the player character
	//myCharacter = new Character(mRenderer, "Images/Mario.png", Vector2D(64, 330));
	mMarioCharacter = new CharacterPlayable(mRenderer, "Images/Mario.png", Vector2D(64, 330), SDLK_w, SDLK_d, SDLK_a, mLevelMap, MOVEMENTSPEED);
	mLuigiCharacter = new CharacterPlayable(mRenderer, "Images/Luigi.png", Vector2D(128, 330), SDLK_UP, SDLK_RIGHT, SDLK_LEFT, mLevelMap, MOVEMENTSPEED);

	//Set up our POW block
	mPowBlock = new PowBlock(mRenderer, mLevelMap);
	mScreenshake = false;
	mBackgroundYPos = 0.0f;

	return true;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
										{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//Clear up any old map
	if (mLevelMap != NULL)
		delete mLevelMap;

	//Set the new one
	mLevelMap = new LevelMap(map);
}

void GameScreenLevel1::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(mMarioCharacter->GetCollisionBox(), mPowBlock->GetCollisionBox()) && mPowBlock->IsAvailable())
	{
		//Collided whilst jumping
		if (mMarioCharacter->IsJumping())
		{
			DoScreenshake();
			mPowBlock->TakeAHit();
			mMarioCharacter->CancelJump();
		}
	}
	else if (Collisions::Instance()->Box(mLuigiCharacter->GetCollisionBox(), mPowBlock->GetCollisionBox()) && mPowBlock->IsAvailable())
	{
		//Collided whilst jumping
		if (mLuigiCharacter->IsJumping())
		{
			DoScreenshake();
			mPowBlock->TakeAHit();
			mLuigiCharacter->CancelJump();
		}
	}
}

void GameScreenLevel1::DoScreenshake()
{
	mScreenshake = true;
	mScreenshakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;

	for (unsigned int i = 0; i < mEnemiesAndCoins.size(); i++)
	{
		mEnemiesAndCoins[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemiesAndCoins(float deltaTime, SDL_Event e)
{
	if (!mEnemiesAndCoins.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemiesAndCoins.size(); i++)
		{
			//Check if enemy is on the bottom row of tiles
			if (mEnemiesAndCoins[i]->GetPosition().y > 300.0f)
			{
				if (mEnemiesAndCoins[i]->GetPosition().x < (float)(-mEnemiesAndCoins[i]->GetCollisionBox().width * 0.5f) ||
					mEnemiesAndCoins[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemiesAndCoins[i]->GetCollisionBox().width * 0.55f))
					mEnemiesAndCoins[i]->SetAlive(false);
			}

			//Now do the update
			mEnemiesAndCoins[i]->Update(deltaTime, e);

			//Check to see if the enemy collides with the player
			if ((mEnemiesAndCoins[i]->GetPosition().y > 300.0f || mEnemiesAndCoins[i]->GetPosition().y <= 64.0f) &&
				mEnemiesAndCoins[i]->GetPosition().x < 64.0f || mEnemiesAndCoins[i]->GetPosition().x > SCREEN_WIDTH - 96.0f)
			{
				//ignore the collisions if the enemy is behind a pipe?
			}
			else 
			{
				if (Collisions::Instance()->Circle(mEnemiesAndCoins[i], mMarioCharacter))
				{
					mEnemiesAndCoins[i]->OnPlayerCollision(mMarioCharacter);
				}
				else if (Collisions::Instance()->Circle(mEnemiesAndCoins[i], mLuigiCharacter))
				{
					mEnemiesAndCoins[i]->OnPlayerCollision(mLuigiCharacter);
				}
			}

			//If the enemy is no longer alive, then schedule it for deletion
			if (!mEnemiesAndCoins[i]->GetAlive())
				enemyIndexToDelete = i;
		}

		if (enemyIndexToDelete != -1)
		{
			delete mEnemiesAndCoins[enemyIndexToDelete];
			mEnemiesAndCoins.erase(mEnemiesAndCoins.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* koopaCharacter = new CharacterKoopa(mRenderer, "Images/Koopa.png", position, mLevelMap, direction, speed);
	mEnemiesAndCoins.push_back(koopaCharacter);
}

void GameScreenLevel1::CreateCoin(Vector2D position, FACING direction, float speed)
{
	CharacterCoin* coinCharacter = new CharacterCoin(mRenderer, "Images/Coin.png", position, mLevelMap, direction, speed);
	mEnemiesAndCoins.push_back(coinCharacter);
}
