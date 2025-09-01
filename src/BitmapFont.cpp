#include "../inc/BitmapFont.h"
#include "../inc/common.h"
#include <cmath>
#include <iostream>
#include <memory>

using namespace bbq;

BitmapFont::BitmapFont(SpriteSheet* spriteSheet, std::string text)
    : spriteSheet_(spriteSheet),
      fontTexture_(nullptr),
      text_(text)
{
}

BitmapFont::~BitmapFont()
{
    SDL_DestroyTexture(fontTexture_);
}

void bbq::BitmapFont::setText(std::string const& text)
{
    text_ = text;
}

int bbq::BitmapFont::getWidth()
{
    int width = 0;
    SDL_QueryTexture(fontTexture_, NULL, NULL, &width, NULL);
    return width;
}

void BitmapFont::draw(SDL_Renderer* renderer, int xPos, int yPos, float dt)
{
    // TODO: this is a bit messy!

    SDL_Rect srcRect  = { 0, 0, 8, 8 };
    SDL_Rect destRect = { 0, 0, 8 * 5, 8 * 5 };
    if ( !fontTexture_ )
    {
        fontTexture_ = SDL_CreateTexture(
            renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
    }
    SDL_SetTextureAlphaMod(fontTexture_, 0xff); // can be used to lower opacity of font
    SDL_SetTextureBlendMode(fontTexture_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, fontTexture_);
    SDL_RenderClear(renderer);

    //sineSeed *= 0.0008f;
    for ( auto& letter : text_ )
    {
        srcRect.x = (letter - ' ') * 8;
        SDL_RenderCopyEx(renderer, spriteSheet_->texture_, &srcRect, &destRect, 0, NULL, SDL_FLIP_NONE);

        destRect.x += 8 * 5;
    }

    int width  = 0;
    int height = 0;
    SDL_QueryTexture(fontTexture_, NULL, NULL, &width, &height);
    SDL_Rect textureDest = { xPos, yPos, width, height };
    SDL_SetRenderTarget(renderer, NULL); // detatch fontTexture_
    SDL_RenderCopy(renderer, fontTexture_, NULL, &textureDest);
}
