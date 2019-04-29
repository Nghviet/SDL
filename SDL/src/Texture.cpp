#include "../include/Texture.h"
#include "../include/Variable.h"
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
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		width = 0;
		height = 0;
	}
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

	SDL_SetColorKey(load, SDL_TRUE, SDL_MapRGB(load->format, 255, 255, 255));
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

void Texture::render(int x, int y, SDL_Rect* clip, double scale, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect render = { x,y,0,0 };
	if (clip == NULL)
	{
		render.w = width * scale;
		render.h = height * scale;
	}
	else
	{
		render.w = clip->w * scale;
		render.h = clip->h * scale;
	}
	if (center == NULL)
	{

		render.x -= render.w / 2;
		render.y -= render.h / 2;
	}
	else
	{
		render.x -= center->x;
		render.y -= center->y;
	}

	SDL_RenderCopyEx(gRenderer, mTexture, clip, &render, angle, center, flip);
}

TextBox::TextBox()
{
	mTexture = NULL;
	width = 0;
	height = 0;
	x = 0;
	y = 0;
	link = -1;
	chosen = false;
}

TextBox::~TextBox()
{
	free();
}

void TextBox::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		width = 0;
		height = 0;
		x = 0;
		y = 0;
		link = -1;
		chosen = false;
	}
}

bool TextBox::load(std::string text,SDL_Color color,int _link)
{
	free();
	SDL_Surface* surface = TTF_RenderText_Solid(gFont, text.c_str(), color);
	if (surface == NULL)
	{
		std::cout << TTF_GetError() << std::endl;
		return false;
	}
	mTexture = SDL_CreateTextureFromSurface(gRenderer, surface);
	if (mTexture == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}
	width = surface->w;
	height = surface->h;
	SDL_FreeSurface(surface);
	link = _link;
	return true;
}

void TextBox::setLocation(int _x, int _y)
{
	x = _x;
	y = _y;
}

void TextBox::render(SDL_Rect*clip, double scale)
{
	update();
	SDL_Rect render = { x,y,0,0 };
	if (clip == NULL)
	{
		render.w = width * scale;
		render.h = height * scale;
	}
	else
	{
		render.w = clip->w * scale;
		render.h = clip->h * scale;
	}

	render.x -= render.w / 2;
	render.y -= render.h / 2;

	if (chosen) gTexture[2]->render(x, y, NULL, scale, 0, NULL, SDL_FLIP_NONE);
	else gTexture[1]->render(x, y, NULL, scale, 0, NULL, SDL_FLIP_NONE);

	SDL_RenderCopyEx(gRenderer, mTexture, clip, &render, 0, NULL, SDL_FLIP_NONE);
}

void TextBox::update()
{
	if (mousePos.x >= x - 200 && mousePos.x <= x + 200 &&
		mousePos.y >= y - 50 && mousePos.y <= y + 50)
	{
		chosen = true;
	}
	else
	{
		chosen = false;
	}
}

bool TextBox::action()
{
	if (chosen&&left) return true;
	else return false;
}

void drawRect(int x1, int y1, int x2, int y2)
{
	SDL_Rect tmp = { x1,y1,x2 - x1,y2 - y1 };
	SDL_RenderDrawRect(gRenderer, &tmp);
}