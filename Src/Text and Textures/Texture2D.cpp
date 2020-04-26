#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>

using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer):
	mRenderer(renderer), mTexture(NULL), mWidth(0), mHeight(0)
{
}

Texture2D::~Texture2D()
{
	Free();
	mRenderer = NULL;
}

bool Texture2D::LoadFromFile(std::string path)
{
	//Remove the memory used for a previous texture
	Free();

	SDL_Surface* pSurface = IMG_Load(path.c_str());
	if (pSurface != NULL)
	{
		//Color key the image - The color to be transparent
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));
		
		//Create the texture from the surface
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
		if (mTexture == NULL)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}
		else 
		{
			//Set the dimensions
			mWidth = pSurface->w;
			mHeight = pSurface->h;
		}

		//Remove the loaded surface now that we have the texture
		SDL_FreeSurface(pSurface);
	}
	else
	{
		cout << "Unable to create texture from surface. Error: " << IMG_GetError() << endl;
	}

	//Return whether the process was successful
	return mTexture != NULL;
}

void Texture2D::Free()
{
	//Check if the texture exists before removing it
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0; mHeight = 0;
	}
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
{
	//Set where to render the texture
	SDL_Rect renderLocation = { newPosition.x, newPosition.y, mWidth, mHeight };

	//Render to screen
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, angle, NULL, flip);
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, Uint8 alphaMod, double angle)
{
	//Set the alpha of the entire texture
	SDL_SetTextureAlphaMod(mTexture, alphaMod);

	//Set where to render the texture
	SDL_Rect renderLocation = { newPosition.x, newPosition.y, mWidth, mHeight };

	//Render to screen
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, angle, NULL, flip);

	//Set it back to max so that any renders not using this overload still have the correct alpha
	SDL_SetTextureAlphaMod(mTexture, 255);
}

void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle)
{
	//Render to screen
	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, NULL, flip);
}

void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, Uint8 alphaMod, double angle)
{
	//Set the alpha of the entire texture
	SDL_SetTextureAlphaMod(mTexture, alphaMod);

	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, NULL, flip);

	//Set it back to max so that any renders not using this overload still have the correct alpha
	SDL_SetTextureAlphaMod(mTexture, 255);
}
