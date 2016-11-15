#include "game.hpp"

// Callback function
void KeyInput(int key, int x, int y)
{
  Game::Instance().KeyInput(key);
}

// Callback function
void Draw()
{
  Game::Instance().Tick();
}

// Callback function
void Timer(int = 0)
{
  if (Game::Instance().m_exitGame)
    Game::Instance().Tick();
}

int main (int argc, char **argv)
{
  Game::Instance().Start();

  // Load game window

  return 0;
}