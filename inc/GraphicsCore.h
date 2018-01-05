#pragma once

#include <iostream>

#include "SDL.h"

namespace bbq
{
  class GraphicsCore
  {
  public:
    GraphicsCore();
    ~GraphicsCore();

    int init();
    int clear();
    SDL_Renderer* getRenderer();

	void drawLine(int x1, int y1, int x2, int y2, uint32_t color);
  private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;
  };
}

