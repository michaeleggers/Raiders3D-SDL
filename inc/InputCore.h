#pragma once

namespace bbq
{
  class InputCore
  {
  public:
    InputCore();
    ~InputCore();

    int init();
    int update();

    bool keyDown(int key);
    bool keyHit(int key);
    bool keyUp(int key);

  private:
    int numKeys_;
    bool* keys_;
    bool* keysPrev_;
  };
}

