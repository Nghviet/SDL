#include "../include/Action.h"
#include "../include/Variable.h"
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

	if (TTF_Init() == -1)
	{
		std::cout << TTF_GetError() << std::endl;
		return false;
	}

	gFont = TTF_OpenFont("arial.ttf", 26);
	if (gFont == NULL)
	{
		std::cout << TTF_GetError() << std::endl;
		return false;
	}

	return true;
}

bool load(void *data)
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
		std::cout << n << std::endl;
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

bool loadText(void* data)
{
	std::ifstream in;
	in.open("loadText.txt", std::fstream::in);
	if (!in.good()) return false;
	int n;
	in >> n;
	while (n--)
	{
		std::string t;
		int r, g, b, a,link;
		std::shared_ptr<TextBox> tmp(new TextBox);
		in >> t >> r >> g >> b >> a >> link;
		std::cout << "Loaded " << t << " " << r << " " << g << " " << b << " " << a << std::endl;
		tmp->load(t, { (Uint8)r,(Uint8)g,(Uint8)b ,(Uint8)a },link);
		gText.push_back(tmp);
	}

	in.close();
	return true;

}

bool loadDebug(void* data)
{
	std::ifstream in;
	in.open("debug.txt");
	if (!in.good()) return false;
	int n;
	in >> n;
	for (int i = 0; i < n; i++)
	{
		double x, y;
		int type;
		double scale,angle;
		in >> x >> y >> angle >> type >> scale;
		std::cout << x << " " << y << " " << angle << " " << type << " " << scale << std::endl;
//		Ship tmp = Ship(Point(x, y), 100 * scale, 50 * scale, scale, angle, type);
//		testing.push_back(tmp);
	}
	in.close();
	return true;
}

void set()
{
	gText[BATTLE]->setLocation(sWidth / 2, sHeight / 8 - 50);
	gText[SURRENDER]->setLocation(sWidth / 2, sHeight / 8);
	gText[RESUME]->setLocation(sWidth / 2, sHeight / 8 + 150);
	gText[OPTION]->setLocation(sWidth / 2, sHeight / 8 + 300);
}

void close()
{
	for (auto &i : gTexture) i->free();
	for (auto &i : gText) i->free();
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	TTF_CloseFont(gFont);
	gRenderer = NULL;
	gWindow = NULL;
	gFont = NULL;
	SDL_Quit();
	TTF_Quit();
}