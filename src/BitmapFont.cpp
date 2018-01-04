#include "../inc/BitmapFont.h"
#include <iostream>

using namespace bbq;

BitmapFont::BitmapFont(Sprite * sprite, std::string text) : sprite_(sprite), text_(text)
{
}

BitmapFont::~BitmapFont()
{
}

void BitmapFont::update()
{
}

void BitmapFont::draw(SDL_Renderer * renderer, int currentFrame)
{
  SDL_Rect dest = { 0, 0, sprite_->width_, sprite_->height_ };
  for (auto& letter : text_)
  {
    SDL_RenderCopyEx(renderer, sprite_->getTexture_(), &sprite_->getFrame_(letter - ' '), &dest, 0, NULL, SDL_FLIP_NONE);
    dest.x += sprite_->width_;
  }
}
