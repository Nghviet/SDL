#include "Texture.h"
#include "Variable.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
Texture::Texture()
{
	mTexture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	free();
}

void Texture::free()
{
	SDL_DestroyTexture(mTexture);
	mTexture = NULL;
	width = 0;
	height = 0;
}

bool Texture::load(std::string path)
{
	free();
	SDL_Texture* input;
	SDL_Surface* load = IMG_Load(path.c_str());
	if (load == NULL)
	{
		std::cout << IMG_GetError() << std::endl;
		return false;
	}

	SDL_SetColorKey(load, SDL_TRUE, SDL_MapRGB(load->format, 0, 0, 255));
	input = SDL_CreateTextureFromSurface(gRenderer, load);
	if (input == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	width = load->w;
	height = load->h;
	mTexture = input;
	SDL_FreeSurface(load);
	return true;
}

void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect render = { x,y,width,height };
	if (clip != NULL)
	{
		render.w = clip->w;
		render.h = clip->h;
	}
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &render, angle, center, flip);
}