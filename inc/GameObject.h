#pragma once

#include "SDL.h"

namespace bbq
{

  class GameObject
  {
  public:
    GameObject();
    virtual ~GameObject();

    virtual void update() = 0;
    virtual void draw(SDL_Renderer*, int currentFrame = 0) = 0;

  };
}

