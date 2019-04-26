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

	int x_battle = sWidth / 2;
	int y_battle = sHeight / 8 - 50;



	bool left;
	bool right;
	while (!quit)
	{
		left = false;
		right = false;

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT) left = true;
				if (e.button.button == SDL_BUTTON_RIGHT) right = true;
			}
		}
		SDL_RenderClear(gRenderer);
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0);
		
		gTexture[11]->render(sWidth / 2, sHeight / 2, NULL, 1, 0, NULL, SDL_FLIP_NONE);
		
		mouse.update();
		if (mousePos.x >= x_battle - 200 && mousePos.x <= x_battle + 200
			&& mousePos.y >= y_battle - 50 && mousePos.y <= y_battle + 50 )
		{
			gTexture[2]->render(x_battle, y_battle, NULL, 2, 0, NULL, SDL_FLIP_NONE);
			if (left)
			{
				UImode = BATTLE;
				return;
			}
		}
		else gTexture[1]->render(x_battle, y_battle, NULL, 2, 0, NULL, SDL_FLIP_NONE);

		gText[0]->render(x_battle, y_battle, NULL, 2);
		

		SDL_RenderPresent(gRenderer);
	}
}

void battle()
{
	int x_surrender = sWidth / 2;
	int y_surrender = sHeight / 8;

	int x_resume = sWidth / 2;
	int y_resume = sHeight / 8 + 150;

	int x_option = sWidth / 2;
	int y_option = sHeight / 8 + 300;

	testing[0].init(480, 540);

	bool left;
	bool right;
	Point tmp;
	bool pause = false;
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
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT) left = true;
				if (e.button.button == SDL_BUTTON_RIGHT) right = true;
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
		for(auto i:testing)
		gTexture[11]->render(i.cur.x, i.cur.y, NULL, i.scale, i.angle, NULL, SDL_FLIP_NONE);

		if(pause)
		{
			if (mousePos.x >= x_surrender - 200 && mousePos.x <= x_surrender + 200 &&
				mousePos.y >= y_surrender - 50 && mousePos.y <= y_surrender + 50)
			{
				gTexture[2]->render(x_surrender, y_surrender, NULL, 2, 0, NULL, SDL_FLIP_NONE);
				if (left)
				{
					UImode = MAIN_MENU;
					return;
				}
			}
			else gTexture[1]->render(x_surrender, y_surrender, NULL, 2, 0, NULL, SDL_FLIP_NONE);
			gText[2]->render(x_surrender, y_surrender, NULL, 2);
		

			if (mousePos.x >= x_resume - 200 && mousePos.x <= x_resume + 200 &&
				mousePos.y >= y_resume - 50 && mousePos.y <= y_resume + 50)
			{
				gTexture[2]->render(x_resume, y_resume, NULL, 2, 0, NULL, SDL_FLIP_NONE);
				if (left)
				{
					UImode = BATTLE;
					pause = false;
				}
			}
			else gTexture[1]->render(x_resume, y_resume, NULL, 2, 0, NULL, SDL_FLIP_NONE);
			gText[1]->render(x_resume, y_resume, NULL, 2);


			if (mousePos.x >= x_option - 200 && mousePos.x <= x_option + 200 &&
				mousePos.y >= y_option - 50 && mousePos.y <= y_option + 50)
			{
				gTexture[2]->render(x_option, y_option, NULL, 2, 0, NULL, SDL_FLIP_NONE);
				if (left)
				{
					UImode = BATTLE;
					pause = false;
				}
			}
			else gTexture[1]->render(x_option, y_option, NULL, 2, 0, NULL, SDL_FLIP_NONE);
			gText[3]->render(x_option, y_option, NULL, 2);

		}


		SDL_RenderPresent(gRenderer);
	}
}