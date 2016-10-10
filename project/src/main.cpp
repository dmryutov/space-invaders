#include "game.hpp"

Game game;

// Callback function
void KeyInput(int key, int x, int y)
{
  game.KeyInput(key);
}

// Callback function
void Draw()
{
  game.Tick();
}

// Callback function
void Timer(int = 0)
{
  game.Tick();
}

int main (int argc, char **argv)
{
  game.Start();

  // Load game window

  return 0;
}