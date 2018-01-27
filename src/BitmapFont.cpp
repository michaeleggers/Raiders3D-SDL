#include "../inc/BitmapFont.h"
#include <iostream>
#include <memory>
#include "../inc/common.h"

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
  SDL_Rect srcRect = { 0, 0, 8, 8};
  SDL_Rect destRect = { 0, 0, 8 * 10, 8 * 10};
  texture = SDL_CreateTexture(renderer
    , SDL_PIXELFORMAT_RGB888
    , SDL_TEXTUREACCESS_TARGET
    , WINDOW_WIDTH
    , WINDOW_HEIGHT);
  SDL_SetTextureAlphaMod(texture, 0xff); // can be used to lower opacity of font 
  SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
  SDL_SetRenderTarget(renderer, texture);
  SDL_RenderClear(renderer);

  //sineSeed *= 0.0008f;
  for (auto& letter : text_)
  {
    sineSeed += 0.0002;
    destRect.y = sin(sineSeed) * 16.0f;
    srcRect.x = (letter - ' ') * 8;
    SDL_RenderCopyEx(renderer
      , spriteSheet_->texture_
      , &srcRect
      , &destRect
      , 0
      , NULL
      , SDL_FLIP_NONE);

    destRect.x += 8 * 10;
  }

  SDL_SetRenderTarget(renderer, NULL);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_DestroyTexture(texture);
}
