#include"../include/UI.h"
#include"../include/Variable.h"
#include"../include/Action.h"
#include<iostream>
#include<SDL.h>
#include<math.h>
#include<algorithm>

int UImode = MAIN_MENU;

/*           MAIN CONTROL                                  */

void mainUIControl()
{
	switch (UImode)
	{
		case MAIN_MENU:
		{
			main_menu();
			break;
		}
		case BATTLE:
		{
			battle();
			return;
		}
	}
}

void loading()
{
	
}

void main_menu()
{

	player.init(sWidth / 2, sHeight / 2);
	player.resize(1);
	while (!quit)
	{
		left = false;
		right = false;
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
				return;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				switch (e.button.button)
				{
					case SDL_BUTTON_LEFT:
						left = true;
						break;
					case SDL_BUTTON_RIGHT:
						right = true;
						break;
				}
			}
		}

		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0);
		SDL_RenderClear(gRenderer);
		
		mouse.update();
		player.update();
		player.render();
//		if (player.turret[0].fired || player.turret[1].fired || player.turret[2].fired)std::cout << "Fired" << std::endl;

		gText[BATTLE]->render(NULL, 2);
		if (gText[BATTLE]->action())
		{
			UImode = BATTLE;
			return;
		}

		SDL_RenderPresent(gRenderer);
	}
}

void battle()
{
	player.init(480, 540);
	player.resize(0.08);
	Point tmp;
	bool pause = false;
	bool option = false;
	while (!quit)
	{
		left = false;
		right = false;

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
				return;
			}
			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
					case SDLK_UP:
					{
						if (!pause) player.movex = std::min(1, player.movex + 1);
					//	std::cout << player.movex << std::endl;
						break;
					}
					case SDLK_DOWN:
					{
						if (!pause) player.movex = std::max(-1, player.movex - 1);
					//	std::cout << player.movex << std::endl;
						break;
					}
					case SDLK_LEFT:
					{
						if (!pause) player.movey = std::max(-1, player.movey - 1);
					//	std::cout << player.movey << std::endl;
					//	std::cout << "left" << std::endl;
						break;
					}
					case SDLK_RIGHT:
					{
						if (!pause) player.movey = std::min(1, player.movey + 1);
					//	std::cout << player.movey << std::endl;
					//	std::cout << "right" << std::endl;
						break;
					}
					case SDLK_ESCAPE:
					{
						pause = (pause + 1) % 2;
						break;
					}
				}
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				switch (e.button.button)
				{
				case SDL_BUTTON_LEFT:
					left = true;
					break;
				case SDL_BUTTON_RIGHT:
					right = true;
					break;
				}
			}
		}
		
		mouse.update();

		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0);
		SDL_RenderClear(gRenderer);
		if (!pause) 
		{ 
			player.move(); 
		}
		player.update();
		player.render();

		if(pause)
		{
			player.current = SDL_GetTicks();

			gText[RESUME]->render(NULL, 2);
			gText[SURRENDER]->render(NULL, 2);
			gText[OPTION]->render(NULL, 2);
			
			if (gText[RESUME]->action())
			{
				pause = false;
			}
			if (gText[SURRENDER]->action())
			{
				UImode = MAIN_MENU;
				return;
			}
		}



		SDL_RenderPresent(gRenderer);
	}
}