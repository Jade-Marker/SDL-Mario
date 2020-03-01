#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"

using namespace::std;

//Globals
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
GameScreenManager* gameScreenManager = NULL;
Uint32 gOldTime;

//Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update(double& angle);
void Render(double angle);

int main(int argc, char* args[])
{
	double angle = 0.0;

	//Check if SDL was set up correctly
	if (InitSDL())
	{
		//Set up the game screen manager - start with level1
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_INTRO);
		gOldTime = SDL_GetTicks();

		//Flag to check if we wish to quit
		bool quit = false;

		//Game Loop
		while (!quit)
		{
			Render(angle);
			quit = Update(angle);
		}
	}

	//close Window and free resources
	CloseSDL();

	return 0;
}

bool InitSDL() 
{
	//Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SLD did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//All good, so attempt to create the window.
		gWindow = SDL_CreateWindow("Games Engine Creation",
									SDL_WINDOWPOS_UNDEFINED,
									SDL_WINDOWPOS_UNDEFINED,
									SCREEN_WIDTH,
									SCREEN_HEIGHT,
									SDL_WINDOW_SHOWN);

		//Did the window get created?
		if (gWindow == NULL)
		{
			//Nope
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer != NULL)
		{
			//Initialise PNG Loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}
		}
		else 
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}
		return true;
	}
}

void CloseSDL()
{
	//Destroy the game screen manager
	delete gameScreenManager;
	gameScreenManager = NULL;

	//Release the renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//Release the window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

bool Update(double& angle)
{
	//Get the new time
	Uint32 newTime = SDL_GetTicks();

	//Event Handler
	SDL_Event e;

	//Get the events
	SDL_PollEvent(&e);

	//Handle any events
	switch (e.type)
	{
	//Click the 'X' to quit
	case SDL_QUIT:
		return true;
		break;

	case SDL_MOUSEBUTTONDOWN:
		return (e.button.button == SDL_BUTTON_RIGHT);
		break;

	case SDL_KEYUP:
		if (e.key.keysym.sym == SDLK_q)
			return true;
		break;
	case SDL_KEYDOWN:
		if (e.key.keysym.sym == SDLK_d)
			angle += 5.0;
		if (e.key.keysym.sym == SDLK_a)
			angle -= 5.0;
		break;
	}

	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);

	//Set the current time to be the old time
	gOldTime = newTime;

	return false;
}

void Render(double angle)
{
	//Clear the screen - black
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);

	gameScreenManager->Render();

	SDL_RenderPresent(gRenderer);
}