#include "../inc/GraphicsCore.h"

using namespace bbq;

GraphicsCore::GraphicsCore() : window_(nullptr), renderer_(nullptr)
{
}

GraphicsCore::~GraphicsCore()
{
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
}

int GraphicsCore::init()
{
  int errorCode = 0;
  if (errorCode = (SDL_Init(SDL_INIT_EVERYTHING) < 0)) 
  {
    std::cout << "couldn't init SDL2. ERROR: " << SDL_GetError() << std::endl;
  }
  
  window_ = SDL_CreateWindow(
    "Barbecue",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    1024, 768,
    0
    );

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
  SDL_RenderSetLogicalSize(renderer_, 1024, 768);

  return errorCode;
}

int GraphicsCore::clear()
{
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderClear(renderer_);
  return 0;
}

SDL_Renderer * GraphicsCore::getRenderer()
{
  return renderer_;
}

void bbq::GraphicsCore::drawLine(int x1, int y1, int x2, int y2, uint32_t color)
{
	SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer_, x1, y1, x2, y2);
}
