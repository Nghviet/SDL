#pragma once
#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <memory>
#include <future>
#include "../include/Texture.h"
#include "../include/Ship.h"
#include "../include/Controller.h"

typedef std::vector<SDL_Rect> vSDLR;

extern int sWidth;
extern int sHeight;

const int UI_TEXT_WIDTH = 100;
const int UI_TEXT_HEIGHT = 100;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern TTF_Font* gFont;
extern std::vector< std::shared_ptr<Texture> > gTexture;
extern std::vector< std::shared_ptr<TextBox> > gText;
extern std::vector<vSDLR> gClip;
extern Uint32 start, end;
extern SDL_Event e;
extern Texture tmp;

extern std::vector<ship> listAllied;
extern std::vector<ship> listEnemy;

extern std::vector<Ship> testing;
extern std::vector< std::shared_ptr<Ship> > controlling;
extern std::vector<std::shared_ptr<Texture> > temp;
const int BB = 1;
const int CA = 2;

extern Mouse mouse;
extern Point mousePos;
extern int UImode;

extern Ship player;

extern bool left;
extern bool right;

extern bool quit;

enum MODE
{
	BATTLE,
	RESUME,
	SURRENDER,
	OPTION,
	PAUSE,
	MAIN_MENU
};

#endif // !VARIABLE_H_
