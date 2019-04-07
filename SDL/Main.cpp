#include <iostream>
#include <SDL.h>
#include <SDL_thread.h>
#include <thread>
#include <future>
#include <assert.h>
#include <chrono>


#include "Action.h"
#include "Variable.h"
#include "Thread.h"
using namespace std;

int main(int argc, char * argv[])
{
	if (!init()) return 0;
	

	tmp.load("img/load.png");
	
	thread loadData(&loadThread);
//	thread loadRen(&loadRender, move(fSignal));
//	if (loadRen.joinable()) loadRen.join();
	while (fSignal.wait_for(std::chrono::milliseconds(1000)) == std::future_status::timeout)
	{
		SDL_RenderClear(gRenderer);
		tmp.render(0, 0, NULL, NULL, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(gRenderer);
		std::cout << "Rendering" << std::endl;
		SDL_Delay(1000);
	}



	int x1, y1;  //origin
	int x2, y2;  //destination
	int xt, yt;  //temp

	cout << "Continued" << endl;

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
		}
		if (SDL_GetMouseState(&xt,&yt) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			x2 = xt; y2 = yt;
		}
		else
		{
			x1 = xt; y1 = yt;
			x2 = x1; y2 = y1;
		}

		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0);
		SDL_RenderClear(gRenderer);

		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		drawRect(x1, y1, x2, y2);

		SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 0);
		SDL_RenderPresent(gRenderer);
	}
}