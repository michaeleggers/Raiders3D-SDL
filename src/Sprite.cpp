#include <iostream>

#include "../inc/Sprite.h"

using namespace bbq;

bbq::Sprite::Sprite() : spriteSheet_(nullptr)
{
}

Sprite::Sprite(
  SpriteSheet* spriteSheet,
  int width,
  int height,
  Uint32 start_x,
  Uint32 start_y,
  Uint8 frames
)
  :
  width_(width),
  height_(height)
{
	spriteSheet_ = spriteSheet;
	frames_ = frames;

	Uint32 maxFramesPerRow = spriteSheet_->width_ / width;
	Uint32 maxFramesPerCol = spriteSheet_->height_ / height;

	std::cout << maxFramesPerRow << " " << maxFramesPerCol << std::endl;


	for (int index = 0; index < frames_; ++index)
	{
		SDL_Rect frame = 
		{ 
			(start_x + index * width) % spriteSheet_->width_, // top left x
			(((width * index) / spriteSheet_->width_) * height) + start_y,	   // top left y
			width,								   // x + width
			height								   // y + height
		};
		frameRegions_.push_back(frame);
		std::cout << "frame " << index << ", x: " << frame.x << ", y: " << frame.y << std::endl;
	}

  //posAndScale_ = { 0, 0, width, height };
}

Sprite::~Sprite()
{
}

SDL_Texture * Sprite::getTexture_()
{
	return spriteSheet_->texture_;
}

SDL_Rect Sprite::getFrame_(Uint8 index)
{
  if (index >= frameCnt_())
  {
    return frameRegions_.at(0);
  }
	return frameRegions_.at(index);
}

Uint8 Sprite::frameCnt_()
{
	return frames_;
}



