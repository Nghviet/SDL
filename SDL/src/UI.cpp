#include"../include/UI.h"
#include"../include/Variable.h"

#include<iostream>

int UImode = MAIN_MENU;

std::pair<int,int> renderText(int x, int y, std::string text,SDL_Color color)
{
	SDL_Surface *surface = TTF_RenderText_Solid(gFont, text.c_str(), color);
	if (surface == NULL)
	{
		std::cout << TTF_GetError() << std::endl;
		return std::pair<int, int>(-1, -1);
	}

	SDL_Texture *texture;
	texture = SDL_CreateTextureFromSurface(gRenderer, surface);
	if (texture == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		return std::pair<int,int> (-1,-1);
	}

	int width = surface->w;
	int height = surface->h;
	SDL_Rect tmp = { x - width / 2,y - height / 2,width,height };
	SDL_RenderCopyEx(gRenderer, texture, NULL, &tmp, 0, NULL, SDL_FLIP_NONE);
	SDL_FreeSurface(surface);
	return std::pair<int, int>(width, height);
}

void mainUIControl()
{
	switch (UImode)
	{
		case MAIN_MENU:
		{

		}
	}
}

void loading()
{
	
}

void main_menu()
{
	while (1)
	{
		SDL_RenderClear(gRenderer);

		SDL_RenderPresent(gRenderer);
	}
}

void battle()
{
	for (auto i : testing)
	{
		//	cout << i.chosen << " " << i.x << " " << i.y << endl;
		if (i.chosen)
		{
			gTexture[8]->render(i.cur.x, i.cur.y, NULL, i.scale, i.angle, NULL, SDL_FLIP_NONE);
		}
		switch (i.branch)
		{
			case BB: {
				gTexture[2]->render(i.cur.x, i.cur.y, NULL, i.scale, i.angle, NULL, SDL_FLIP_NONE);
				break;
			}
			case CA: {
				gTexture[3]->render(i.cur.x, i.cur.y, NULL, i.scale, i.angle, NULL, SDL_FLIP_NONE);
				break;
			}
		}
	}
}