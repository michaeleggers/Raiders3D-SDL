#include "../inc/SpriteSheet.h"
#include "SDL_image.h"
#include <iostream>

bbq::SpriteSheet::SpriteSheet(SDL_Renderer* renderer, const char* file, Uint32 key)
{
	SDL_Surface* surface = NULL;
	surface = IMG_Load(file);
	if (!surface) {
		std::cerr << "could not create surface from file " << std::string(file) << " ERROR: " << SDL_GetError() << std::endl;
		SDL_Quit(); // later exception handling.
	}

	width_ = surface->w;
	height_ = surface->h;

	if (key) {
		Uint8 r = (key & 0xFF000000) >> 24;
		Uint8 g = (key & 0x00FF0000) >> 16;
		Uint8 b = (key & 0x0000FF00) >> 8;
		int success = SDL_SetColorKey(surface,
			SDL_TRUE,
			SDL_MapRGB(surface->format, r, g, b));

		if (success < 0) {
			std::cerr << "setting the color key failed. ERROR: " << SDL_GetError() << std::endl;
		}
	}

	texture_ = SDL_CreateTextureFromSurface(renderer, surface);
 
	SDL_FreeSurface(surface);
	

}

bbq::SpriteSheet::~SpriteSheet()
{
}
