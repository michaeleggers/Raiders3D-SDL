#pragma once

#include <string>

#include "SDL.h"

#include "../inc/GameObject.h"
#include "../inc/Sprite.h"

namespace bbq
{
class BitmapFont
{
  public:
    BitmapFont(SpriteSheet* spriteSheet, std::string text);
    ~BitmapFont();

    void draw(SDL_Renderer* renderer, int xPos, int yPos, float dt);
    void setText(std::string const& text);
    int  getWidth();

  private:
    SpriteSheet* spriteSheet_;
    SDL_Texture* fontTexture_;
    std::string  text_;
    float        sineSeed_ = .0f;
};

} // namespace bbq
