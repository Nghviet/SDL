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

class TextBox
{
public:
	TextBox();

	~TextBox();

	void free();

	bool load(std::string text, SDL_Color color,int _link);

	void setLocation(int _x, int _y);

	void update();

	bool action();

	void render(SDL_Rect* clip, double scale);

private:
	SDL_Texture *mTexture;
	int width, height;
	int x, y;
	int link;
	bool chosen;

};

void drawRect(int x1, int y1, int x2, int y2);

#endif // !TEXTURE_H_
