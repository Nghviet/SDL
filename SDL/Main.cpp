#include<iostream>
#include<SDL.h>
#include"Action.h"
#include"Variable.h"

using namespace std;

int main(int argc, char * argv[])
{
	if (!init()) return 0;
	if (!load()) return 0;
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

		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0);
		SDL_RenderClear(gRenderer);
		gTexture[0]->render(200, 200, &gClip[0][0], NULL, NULL, SDL_FLIP_NONE);
		SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 0);

		SDL_RenderPresent(gRenderer);
	}
}