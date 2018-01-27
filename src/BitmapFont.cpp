#include "../inc/BitmapFont.h"
#include <iostream>
#include <memory>

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

void bbq::BitmapFont::setText(std::string const & text)
{
  text_ = text;
}

void BitmapFont::draw(SDL_Renderer * renderer, int currentFrame)
{
  // TODO: this is messy!
  // dont create a new texture for each call.
  // figure out how to alpha blend with the render below.
  SDL_Texture* texture;
  SDL_Rect dest = { 0, 0, sprite_->width_, sprite_->height_};
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 616, 8);
  SDL_SetRenderTarget(renderer, texture);
  for (auto& letter : text_)
  {
    SDL_RenderCopyEx(renderer, sprite_->getTexture_(), &sprite_->getFrame_(letter - ' '), &dest, 0, NULL, SDL_FLIP_NONE);
    dest.x += sprite_->width_;
  }
  SDL_SetRenderTarget(renderer, NULL);
  SDL_Rect rect = { 0, 0, 616, 8 };
  SDL_Rect rect2 = { 0, 0, 616 * 10, 8 * 10 };
  SDL_RenderCopy(renderer, texture, &rect, &rect2);
  SDL_DestroyTexture(texture);
}
