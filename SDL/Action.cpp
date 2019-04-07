#include "Action.h"
#include "Variable.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <fstream>
#include <iostream>
bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	if (TTF_Init() < 0)
	{
		std::cout << TTF_GetError() << std::endl;
		return false;
	}

	gWindow = SDL_CreateWindow("Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sWidth, sHeight, SDL_WINDOW_RESIZABLE);
	if (gWindow == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}
	SDL_GetRenderDrawColor(gRenderer, 0, 0, 0, 0);

	int img = IMG_INIT_PNG;
	if (!(IMG_Init(img)&img))
	{
		std::cout << SDL_GetError();
		return false;
	}

	return true;
}

bool load()
{
	std::ifstream in;
	in.open("loadImage.txt", std::fstream::in);
	if (!in.good())
	{
		std::cout << "Load err";
		return false;
	}
	else
	{
		int n;
		in >> n;
		while (n--)
		{
			// Order of render - name - path - number of frame(1 if static) - width(horizontal)(perframe) - height(vertical)(perframe)
			int no, f, w, h;
			std::string name, path;
			in >> no >> name >> path >> f >> w >> h;
			std::shared_ptr<Texture> tmp(new Texture);
			std::vector<SDL_Rect> t;
			if (!tmp->load(path.c_str()))
			{
				std::cout << SDL_GetError() << std::endl;
				return false;
			}
			std::cout << path << " loaded" << std::endl;
			for (int j = 0; j < f; j++)
			{
				SDL_Rect t1 = { w*j,0,w,h };
				t.push_back(t1);
			}
			gTexture.push_back(tmp);
			gClip.push_back(t);
		}
	}
	in.close();

	return true;
}

void close()
{
	for (auto i : gTexture) i->free();
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;
	SDL_Quit();
}