#include"Thread.h"
#include"Variable.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <fstream>
#include <iostream>
int loadThread(void *data)
{
	std::cout << "Thread loading" << std::endl;
	std::ifstream in;
	in.open("loadImage.txt", std::fstream::in);
	if (!in.good())
	{
		std::cout << "Load err";
		loading = false;
		return 0;
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
				return 1;
			}
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
	loading = false;
	std::cout << "Thread loading complete,sending back"<<loading << std::endl;
	return 0;
}