#pragma once
#include "../inc/GameObject.h"
#include "../inc/Sprite.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

namespace bbq
{

class TileMap : public GameObject
{
  public:
    TileMap(std::string const& inputfile, int width, int height, Sprite* sprite);
    ~TileMap();

    void update();
    void draw(SDL_Renderer*, int currentFrame = 0);

    std::vector<char> asciiMap_;
    Sprite*           sprite_;
    int               columns_;
    int               rows_;
};
} // namespace bbq
