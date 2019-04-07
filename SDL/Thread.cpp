#include "Thread.h"
#include "Variable.h"
#include "Texture.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <future>
#include <thread>
#include <assert.h>
#include <fstream>
#include <iostream>
#include <chrono>

void loadThread()
{
	std::cout << "Thread loading" << std::endl;
	std::ifstream in;
	in.open("loadImage.txt", std::fstream::in);
	if (!in.good())
	{
		std::cout << "Load err";
		in.close();
		return;
	}
	else
	{
		int n;
		in >> n;
//		std::cout << n << std::endl;
		while (n--)
		{
			// Order of render - name - path - number of frame(1 if static) - width(horizontal)(perframe) - height(vertical)(perframe)
			int no, f, w, h;
			std::string name, path;
			in >> no >> name >> path >> f >> w >> h; 
//			std::cout << no << std::endl;
			std::shared_ptr<Texture> tmp(new Texture);
			std::vector<SDL_Rect> t;
			if (!tmp->load(path.c_str()))
			{
				std::cout << SDL_GetError() << std::endl;
				in.close();
				return;
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
	std::cout << "Thread loading complete,sending back" << std::endl;
	signal.set_value();
	return;
}

void loadRender()
{
	while (fSignal.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout)
	{
		SDL_RenderClear(gRenderer);
		tmp.render(0, 0, NULL, NULL, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(gRenderer);
		std::cout << "Rendering" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	
//	while (s.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout) std::cout << "Rendering" << std::endl;
	return;
}