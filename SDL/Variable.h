#pragma once
#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <memory>
#include <future>
#include "Texture.h"

typedef std::vector<SDL_Rect> vSDLR;

extern int sWidth;
extern int sHeight;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern TTF_Font* gFont;
extern std::vector< std::shared_ptr<Texture> > gTexture;
extern std::vector<vSDLR> gClip;

static bool loading = true;

static Texture tmp;

extern std::promise<void> signal;
extern std::future<void> fSignal;
#endif // !VARIABLE_H_
