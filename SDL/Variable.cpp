#include "Variable.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;
std::vector< std::shared_ptr<Texture> > gTexture;
std::vector<vSDLR> gClip;

bool loading = true;