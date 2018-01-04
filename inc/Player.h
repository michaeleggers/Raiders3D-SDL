#pragma once

#include <vector>

#include "../inc/GameObject.h"
#include "../inc/Sprite.h"

enum animationState
{
  idle,
  walk,
  attack
};

enum facingState
{
  right,
  left
};

struct Pos2d_t
{
  int x;
  int y;
};


class Player : public bbq::GameObject
{
public:
  Player();
  Player(std::vector<bbq::Sprite*>& sprites);
  ~Player();

  void update() override;
  void draw(SDL_Renderer*, int currentFrame = 0) override;

  std::vector<bbq::Sprite*> sprites_;
  bbq::Sprite* activeSprite_;
  Pos2d_t pos_;
  animationState state_;
  animationState prevState_;
  facingState facingState_;
  SDL_Rect destination_;

};

