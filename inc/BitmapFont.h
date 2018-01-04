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
    void draw(SDL_Renderer*, int currentFrame = 0) override;

  private:
    Sprite* sprite_;
    std::string text_;
  
  };


}

