#pragma once

#include "GraphicsCore.h"
#include "InputCore.h"

namespace bbq
{
  class GameState
  {
  public:
    GameState();
    virtual ~GameState();

    virtual void update(InputCore&) = 0;
    virtual void draw(GraphicsCore&) = 0;
  };

}

