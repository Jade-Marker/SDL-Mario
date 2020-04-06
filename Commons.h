#pragma once

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float initialX, float initialY)
	{
		x = initialX;
		y = initialY;
	}
};

struct Rect2D 
{
	float x;
	float y;
	float width;
	float height;

	Rect2D()
	{
		width = 0.0f;
		height = 0.0f;
		x = 0.0f;
		y = 0.0f;
	}

	Rect2D(float initialX, float initialY, float initialWidth, float initialHeight)
	{
		width = initialWidth;
		height = initialHeight;
		x = initialX;
		y = initialY;
	}
};

struct Circle2D 
{
	float x;
	float y;
	float radius;

	Circle2D()
	{
		x = 0.0f;
		y = 0.0f;
		radius = 0.0f;
	}

	Circle2D(float initialX, float initialY, float initialRadius)
	{
		x = initialX;
		y = initialY;
		radius = initialRadius;
	}
};

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

enum FACING
{
	FACING_LEFT = 0,
	FACING_RIGHT
};

enum INPUT_TYPE
{
	JUMP,
	LEFT,
	RIGHT
};

enum CHARACTERSTATE
{
	PLAYER_DEATH = 0,
	IDLE,
	MOVING,
	JUMPING
};

enum TILE
{
	EMPTY = 0,
	BRICK,
	PIPE_ENTRANCE_LOWER_RIGHT,
	PIPE_ENTRANCE_UPPER_RIGHT,
	PIPE_ENTRANCE_LOWER_LEFT,
	PIPE_ENTRANCE_UPPER_LEFT,
	PIPE_BODY_LOWER,
	PIPE_BODY_UPPER,
	PLATFORM,
	POW_BLOCK
};