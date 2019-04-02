#pragma once
#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <SDL.h>
#include <string>
struct Texture
{
	public:
		Texture();

		~Texture();

		void free();

		bool load(std::string path);	

		void render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);

	private:
		SDL_Texture* mTexture;
		int width, height;
};

#endif // !TEXTURE_H_
