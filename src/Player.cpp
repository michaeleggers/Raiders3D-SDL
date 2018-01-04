#include "../inc/Player.h"

Player::Player()
{
}

void Player::update()
{
  if (state_ == idle)
  {
    activeSprite_ = sprites_[0];
  }
  else if (state_ == walk)
  {
    activeSprite_ = sprites_[1];
  }
  else if (state_ == attack)
  {
    if (prevState_ != attack)
    {
      activeSprite_ = sprites_[2];
    }
  }
  else
  {
    state_ = idle;
  }

  prevState_ = state_;
  destination_ = { pos_.x, pos_.y, activeSprite_->width_, activeSprite_->height_ };
}

void Player::draw(SDL_Renderer * renderer, int currentFrame)
{
  if (facingState_ == facingState::left)
  {
    SDL_RenderCopyEx(renderer, activeSprite_->getTexture_(), &activeSprite_->getFrame_(currentFrame), &destination_, 0, NULL, SDL_FLIP_HORIZONTAL);
  }
  else
  {
    SDL_RenderCopyEx(renderer, activeSprite_->getTexture_(), &activeSprite_->getFrame_(currentFrame), &destination_, 0, NULL, SDL_FLIP_NONE);
  }
}

Player::Player(std::vector<bbq::Sprite *>& sprites) :
  state_(idle),
  sprites_(sprites),
  activeSprite_(sprites_[idle]),
  facingState_(right),
pos_{ 0, 0}
{
}




Player::~Player()
{
}
