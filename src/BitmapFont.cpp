#include "../inc/BitmapFont.h"
#include <iostream>
#include <memory>

using namespace bbq;

BitmapFont::BitmapFont(SpriteSheet * spriteSheet, std::string text) : 
  spriteSheet_(spriteSheet)
  , text_(text)
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
  SDL_Rect srcRect = { 0, 0, spriteSheet_->width_, spriteSheet_->height_};
  SDL_Rect destRect = { 0, 0, spriteSheet_->width_, spriteSheet_->height_};
  texture = SDL_CreateTexture(renderer
    , SDL_PIXELFORMAT_RGB888
    , SDL_TEXTUREACCESS_TARGET
    , 1920
    , 1080);
  SDL_SetTextureAlphaMod(texture, 0xff); 
  SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

  SDL_SetRenderTarget(renderer, texture);
  SDL_RenderCopyEx(renderer
    , spriteSheet_->texture_
    , &srcRect
    , &destRect
    , 0
    , NULL
    , SDL_FLIP_NONE);
  for (auto& letter : text_)
  {
    //dest.x += spriteSheet_->width_;
  }
  SDL_SetRenderTarget(renderer, NULL);
  SDL_Rect rect = { 8, 0, 8, 8 };
  SDL_Rect rect2 = { 0, 0, 8 * 10 , 8 * 10};
  SDL_RenderCopy(renderer, texture, &rect, &rect2);
  SDL_DestroyTexture(texture);
}
