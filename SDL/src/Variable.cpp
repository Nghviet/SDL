#include "../include/Variable.h"

int sWidth = 1600;
int sHeight = 1024;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;
std::vector< std::shared_ptr<Texture> > gTexture;
std::vector< std::shared_ptr<TextBox> > gText;
std::vector<vSDLR> gClip;
std::promise<void> signal;
std::future<void> fSignal = signal.get_future();
Uint32 start, end;
SDL_Event e;

std::vector<Ship> testing;
std::vector< std::shared_ptr<Ship> > controlling;

Mouse mouse;
Point mousePos;

Ship player;

bool left = false;
bool right = false;
bool quit = false;