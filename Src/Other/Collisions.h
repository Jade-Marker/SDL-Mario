#pragma once

#include "Commons.h"

class Character;

class Collisions 
{
private:
	Collisions();

public:
	~Collisions();

	static Collisions* Instance();

	bool Circle(Character* character1, Character* character2);
	bool Circle(Circle2D circle1, Circle2D circle2);
	bool Box(Rect2D rect1, Rect2D rect2);

private:
	static Collisions* mInstance;
};