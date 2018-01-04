#pragma once

/*
	Holds a Texture or Spritesheet in memory. Other
	classes can point to a instance of this class in
	order to render some stuff from it.
*/
#include <string>

# include "SDL.h"

namespace bbq
{
	class SpriteSheet
	{
	public:

		friend class Sprite;

		SpriteSheet(SDL_Renderer* renderer, const char* file, Uint32 key = 0x0);
		~SpriteSheet();

	private:

		SDL_Texture* texture_;
		Uint32 width_;
		Uint32 height_;
	
	};

}
