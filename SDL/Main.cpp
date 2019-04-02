#include <iostream>
#include <SDL.h>
#include <SDL_thread.h>

#include "Action.h"
#include "Variable.h"
#include "Thread.h"
using namespace std;

int main(int argc, char * argv[])
{
	if (!init()) return 0;

	Texture tmp;
	tmp.load("load.png");
	cout << "Tmp load complete" << endl;
	SDL_Thread* loadingThread = SDL_CreateThread(loadThread, "Loading",(void*)(100));

	while (loading)
	{	
		cout << loading << endl;
		SDL_RenderClear(gRenderer);
		tmp.render(0,0,NULL,NULL,NULL,SDL_FLIP_NONE);
		SDL_RenderPresent(gRenderer);
	}

	std::cout << "Recevied" << std::endl;

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