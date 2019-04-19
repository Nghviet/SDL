#pragma once
#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <SDL.h>
#include <string>
class Texture
{
	public:
		Texture();

		~Texture();

		void free();

		bool load(std::string path);	

		void render(int x, int y, SDL_Rect* clip, double scale, double angle, SDL_Point* center, SDL_RendererFlip flip);

	private:
		SDL_Texture* mTexture;
		int width, height;
};

class Text
{
	public:
		Text();

		~Text();

		void free();

};

void drawRect(int x1, int y1, int x2, int y2);

#endif // !TEXTURE_H_
