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
	if (!load(NULL)) return 0;
	if (!loadText(NULL)) return 0;
//	if (!loadDebug(NULL)) return 0;
	set();
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

	cout << gTexture.size() << endl;

	if(0)
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				close();
				return 0;
			}
		}

		mainUIControl();

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

	}

	close();
	return 0;

}