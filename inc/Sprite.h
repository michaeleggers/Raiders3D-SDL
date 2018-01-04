#pragma once

#include <vector>

#include "SpriteSheet.h"

/*
	Takes reference to SpriteSheet and
	renders only the portion (eg Walkcycle) it needs.
*/

namespace bbq
{
	class Sprite
	{
	public:
    Sprite();
		Sprite(
			SpriteSheet* spriteSheet,
			int width, 
			int height,
			Uint32 start_x,
			Uint32 start_y,
			Uint8 frames);
		virtual ~Sprite();

		// expose functions for now
		SDL_Texture* getTexture_();
		SDL_Rect getFrame_(Uint8);
		Uint8 frameCnt_();
    int width_;
    int height_;

	private:
		SpriteSheet* spriteSheet_;
		std::vector<SDL_Rect> frameRegions_;
		uint8_t frames_;
	};

}