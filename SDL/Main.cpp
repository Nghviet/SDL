#include <iostream>
#include <SDL.h>
#include <SDL_thread.h>
#include <thread>
#include <future>
#include <assert.h>
#include <chrono>


#include "../Action.h"
#include "../Variable.h"
#include "../Thread.h"
#include "../Controller.h"
#include "../UI.h"
using namespace std;

vector<Point> rec;

int main(int argc, char * argv[])
{
	if (!init()) return 0;
	if (!load()) return 0;

	if (!loadDebug()) return 0;

	/*
	if (loadRen.joinable()) loadRen.join();
	while (fSignal.wait_for(std::chrono::milliseconds(1000)) == std::future_status::timeout)
	{
		SDL_RenderClear(gRenderer);
		tmp.render(0, 0, NULL, NULL, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(gRenderer);
		std::cout << "Rendering" << std::endl;
		SDL_Delay(1000);
	}
	*/
	
	Uint32 start, end;
	SDL_Event e;
	while (1)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				close();
				return 0;
			}
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
					case SDLK_w:
					{
						for (auto &i : testing) i.movex = min(1, i.movex + 1);
						break;
					}
					case SDLK_s:
					{
						for (auto &i : testing) i.movex = max(-1, i.movex - 1);
						break;
					}
					case SDLK_a:
					{
						for (auto &i : testing) i.movey = max(-1, i.movey - 1);
						break;
					}
					case SDLK_d:
					{
						for (auto &i : testing) i.movey = min(1, i.movey + 1);
						break;
					}
				}
			}
		}

		//Mouse handling
		mouse.update();

		//Keybroad handling
		if(1)
		{
			const Uint8 *state = SDL_GetKeyboardState(NULL);
			if (state[SDL_SCANCODE_ESCAPE])
			{
				for (auto &i : testing) i.chosen = false;
				while (!controlling.empty()) controlling.pop_back();
			}
			if (state[SDL_SCANCODE_W])
			{
			
			}
			if (state[SDL_SCANCODE_S])
			{
				
			}
			
			if (state[SDL_SCANCODE_A])
			{
				
			}
			if (state[SDL_SCANCODE_D])
			{
				
			}
			
		}
		
		for (auto &i : testing) i.move();
		
		

		// Render
		{
			SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0);
			SDL_RenderClear(gRenderer);

			mouse.render();
			
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

			//gTexture[0]->render(sWidth / 2, sHeight / 2, NULL, 2, 0, NULL, SDL_FLIP_NONE);
			
			SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 0);
			SDL_RenderPresent(gRenderer);
		}
	}


}