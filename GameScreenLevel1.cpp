#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"
#include "PowBlock.h"

//Todo
//Fix memory leak with level 1 (can see if you look at memory usage and spam enter) (goes back to atleast week 3!?)
//Remove unused angle stuff from Source.cpp
//Set coins to die when collecting them
//Refactor character so that the code that handles frame stuff is in Character
//Add points to mario when killing coin/enemy
//Implement another enemy (get sprite from here: https://www.spriters-resource.com/arcade/mariobros/sheet/93677/)
//Refactor character so that mario and luigi are of type playableCHaracter inherited from character so that other inherited don't have control map, etc


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

	mEnemies.clear();
}

void GameScreenLevel1::Render()
{
	//Draw the background
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);

	//Draw the enemies
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}

	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Render();
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
		enemySpawnTimer = SPAWN_TIME;
		CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
	}

	UpdateEnemies(deltaTime, e);

	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Update(deltaTime, e);
	}

	//Update the player
	mMarioCharacter->Update(deltaTime, e);
	mLuigiCharacter->Update(deltaTime, e);

	/*if (Collisions::Instance()->Circle(mario, luigi))
	{
		std::cout << "Colliding" << std::endl;
	}*/
	//if (Collisions::Instance()->Box(mario->GetCollisionBox(), luigi->GetCollisionBox()))
	//{
	//	std::cout << "Colliding" << std::endl;
	//}
	if (Collisions::Instance()->Circle(mMarioCharacter->GetCollisionCircle(), mLuigiCharacter->GetCollisionCircle()))
		std::cout << "Colliding" << std::endl;

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
	enemySpawnTimer = SPAWN_TIME;

	CreateCoin(Vector2D(150, 32), FACING_RIGHT, COIN_SPEED);
	CreateCoin(Vector2D(325, 32), FACING_LEFT, COIN_SPEED);

	//Set up the player character
	//myCharacter = new Character(mRenderer, "Images/Mario.png", Vector2D(64, 330));
	mMarioCharacter = new Character(mRenderer, "Images/Mario.png", Vector2D(64, 330), SDLK_w, SDLK_d, SDLK_a, mLevelMap, MOVEMENTSPEED);
	mLuigiCharacter = new Character(mRenderer, "Images/Luigi.png", Vector2D(128, 330), SDLK_UP, SDLK_RIGHT, SDLK_LEFT, mLevelMap, MOVEMENTSPEED);

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

	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!mEnemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			//Check if enemy is on the bottom row of tiles
			if (mEnemies[i]->GetPosition().y > 300.0f)
			{
				if (mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisionBox().width * 0.5f) ||
					mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width * 0.55f))
					mEnemies[i]->SetAlive(false);
			}

			//Now do the update
			mEnemies[i]->Update(deltaTime, e);

			//Check to see if the enemy collides with the player
			if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f) &&
				mEnemies[i]->GetPosition().x < 64.0f || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f)
			{
				//ignore the collisions if the enemy is behind a pipe?
			}
			else 
			{
				if (Collisions::Instance()->Circle(mEnemies[i], mMarioCharacter))
				{
					if (mEnemies[i]->GetInjured())
						mEnemies[i]->SetAlive(false);
					else
						mMarioCharacter->SetState(PLAYER_DEATH);
				}
				else if (Collisions::Instance()->Circle(mEnemies[i], mLuigiCharacter))
				{
					if (mEnemies[i]->GetInjured())
						mEnemies[i]->SetAlive(false);
					else
						mLuigiCharacter->SetState(PLAYER_DEATH);
				}
			}

			//If the enemy is no longer alive, then schedule it for deletion
			if (!mEnemies[i]->GetAlive())
				enemyIndexToDelete = i;
		}

		if (enemyIndexToDelete != -1)
		{
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* koopaCharacter = new CharacterKoopa(mRenderer, "Images/Koopa.png", position, mLevelMap, direction, speed);
	mEnemies.push_back(koopaCharacter);
}

void GameScreenLevel1::CreateCoin(Vector2D position, FACING direction, float speed)
{
	CharacterCoin* coinCharacter = new CharacterCoin(mRenderer, "Images/Coin.png", position, mLevelMap, direction, speed);
	mCoins.push_back(coinCharacter);
}
