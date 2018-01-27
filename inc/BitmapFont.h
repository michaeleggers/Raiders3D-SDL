#pragma once

#include <string>

#include "SDL.h"

#include "../inc/GameObject.h"
#include "../inc/Sprite.h"

namespace bbq
{
  class BitmapFont : public GameObject
  {
  public:
    BitmapFont(Sprite* sprite, std::string text);
    ~BitmapFont();
  
    void update() override;
    void draw(SDL_Renderer* renderer, int currentFrame = 0) override;
    void setText(std::string const & text);

  private:
    Sprite* sprite_;
    std::string text_;
  
  };


}

