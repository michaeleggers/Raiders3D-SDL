

#include "../inc/TileMap.h"

using namespace bbq;


TileMap::TileMap(std::string const & inputfile, int width, int height, Sprite* sprite) : columns_(width), rows_(height), sprite_(sprite)
{
  std::ifstream ifs(inputfile);
  //std::copy(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>(), back_inserter(asciiMap_));

  //std::cout << "drawing map" << std::endl;
  //for (auto& c : asciiMap_)
  //{
  //  std::cout << c << std::endl;
  //}

  asciiMap_ = { '#', '#', '#','#', '#', '#','#', '#', '#','#', '#', '#',
                '#', '#', '#','#', '#', '#','#', '#', '#','#', '#', '#',
                '#', '#', '#','#', '#', '#','#', '#', '#','#', '#', '#',
                '#', '#', '#','0', '0', '0','0', '#', '#','#', '#', '#',
                '#', '#', '#','0', '0', '0','0', '#', '#','#', '#', '#',
                '#', '#', '#','0', '0', '0','0', '#', '#','#', '#', '#',
                '#', '#', '#','#', '#', '#','#', '#', '#','#', '#', '#',
                '#', '#', '#','#', '#', '#','#', '#', '#','#', '#', '#'
  };
  std::cout << "map size: " << asciiMap_.size() << std::endl;
  ifs.close();
}

TileMap::~TileMap()
{
}

void TileMap::update()
{
}

void TileMap::draw(SDL_Renderer * renderer, int currentFrame)
{
  int scale = 3; // todo: make member
  SDL_Rect destination = { 0, 0, sprite_->width_* scale , sprite_->height_ * scale };
  int counter = 100; // just testing
    
    for (int col = 0; col < columns_; ++col)
    {
      for (int row = 0; row < rows_; ++row)
      {
        destination.y = col * sprite_->height_ * scale;
        destination.x = row * sprite_->width_ * scale;
        char tile = asciiMap_[col * columns_ + row];
        if (tile == '#')
        {
          SDL_RenderCopyEx(renderer, sprite_->getTexture_(), &sprite_->getFrame_(counter), &destination, 0, NULL, SDL_FLIP_NONE);
        }
        if (tile == '0')
        {
          SDL_RenderCopyEx(renderer, sprite_->getTexture_(), &sprite_->getFrame_(counter), &destination, 0, NULL, SDL_FLIP_NONE);
        }
        counter++;
      }
    }
}
