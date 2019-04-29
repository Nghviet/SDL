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
	player = Ship(1505, 236, 1, 0, 0);
	player.link(gTexture[12],gTexture[13],gTexture[14]);
	player.init(sWidth / 2, sHeight / 2);

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

			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
					case SDLK_UP: 
						player.angle += 10;
						break;
					case SDLK_DOWN:
						player.angle -= 10;
						break;
					case SDLK_RIGHT:
						player.angleTur[0] += 10;
						break;
					case SDLK_LEFT:
						player.angleTur[0] -= 10;
						break;

					case SDLK_w:
						player.angleTur[1] += 10;
						break;

					case SDLK_s:
						player.angleTur[1] -= 10;
						break;

					case SDLK_e:
						player.angleTur[2] += 10;
						break;

					case SDLK_d:
						player.angleTur[2] -= 10;
						break;

				}

			}

		}

		SDL_RenderClear(gRenderer);
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0);
		
		mouse.update();	
		player.render();

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
					case SDLK_w:
					{
						if (!pause) for (auto &i : testing) i.movex = std::min(1, i.movex + 1);
						break;
					}
					case SDLK_s:
					{
						if (!pause) for (auto &i : testing) i.movex = std::max(-1, i.movex - 1);
						break;
					}
					case SDLK_a:
					{
						if (!pause) for (auto &i : testing) i.movey = std::max(-1, i.movey - 1);
						break;
					}
					case SDLK_d:
					{
						if (!pause) for (auto &i : testing) i.movey = std::min(1, i.movey + 1);
						break;
					}
					case SDLK_ESCAPE:
					{
						pause = (pause + 1) % 2;
						break;
					}
				}
			}
		}

		mouse.update();
		
		SDL_RenderClear(gRenderer);
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0);
		if (!pause)
		{
			for (auto &i : testing) i.move();

		}
		/*
		for (auto i : testing)
			{
				//	cout << i.chosen << " " << i.x << " " << i.y << endl;
				switch (i.branch)
				{
				case BB: {
					gTexture[3]->render(i.cur.x, i.cur.y, NULL, i.scale, i.angle, NULL, SDL_FLIP_NONE);
					break;
				}
				case CA: {
					gTexture[4]->render(i.cur.x, i.cur.y, NULL, i.scale, i.angle, NULL, SDL_FLIP_NONE);
					break;
				}
				}
			}
		*/

		if(pause)
		{
			gText[RESUME]->render(NULL, 2);
			gText[SURRENDER]->render(NULL, 2);
			gText[OPTION]->render(NULL, 2);
			
			if (gText[RESUME]->action())
			{
				pause = false;
			}
			if (1)
			{

			}
		}


		SDL_RenderPresent(gRenderer);
	}
}