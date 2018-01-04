#include "SDL.h"

#include "../inc/InputCore.h"

using namespace bbq;

InputCore::InputCore() : keys_(nullptr), keysPrev_(nullptr)
{

}

InputCore::~InputCore()
{
  delete[] keys_;
  delete[] keysPrev_;
}

int InputCore::init()
{
  Uint8 const * keyBoardState = SDL_GetKeyboardState(&numKeys_);
  keys_ = new bool[numKeys_];
  keysPrev_ = new bool[numKeys_];

  for (int i = 0; i < numKeys_; ++i)
  {
    keys_[i] = keyBoardState[i];
    keysPrev_[i] = false;
  }

  return 0;
}

int InputCore::update()
{
  Uint8 const * keyBoardState = SDL_GetKeyboardState(&numKeys_);

  for (int i = 0; i < numKeys_; ++i)
  {
    keysPrev_[i] = keys_[i];
    keys_[i] = keyBoardState[i];
  }
  
  return 0;
}

bool InputCore::keyDown(int key)
{
  if (key < 0 || key > numKeys_)
    return false;

  return keys_[key];
}

bool InputCore::keyHit(int key)
{
  return false;
}

bool InputCore::keyUp(int key)
{
  if (key < 0 || key > numKeys_)
    return false;
  return (keysPrev_[key] && !keys_[key]);
}
