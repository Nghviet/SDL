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

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern TTF_Font* gFont;
extern std::vector< std::shared_ptr<Texture> > gTexture;
extern std::vector<vSDLR> gClip;

extern Texture tmp;

extern std::vector<ship> listAllied;
extern std::vector<ship> listEnemy;

extern std::vector<Ship> testing;
extern std::vector< std::shared_ptr<Ship> > controlling;
extern std::vector<std::shared_ptr<Texture> > temp;
const int BB = 1;
const int CA = 2;

extern Mouse mouse;

extern int UImode;
#endif // !VARIABLE_H_
