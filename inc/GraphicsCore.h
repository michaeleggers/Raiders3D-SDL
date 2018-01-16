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

	void drawLine(int x1, int y1, int x2, int y2, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 0x00);
  void drawPoint(int x, int y, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 0x00);
  void drawLine(int x1, int y1, int x2, int y2, uint32_t color);
  void drawPoint(int x, int y, uint32_t color);

  private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;
  };
}

