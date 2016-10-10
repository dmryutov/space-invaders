#pragma once

#include "gun.hpp"
#include "alien_group.hpp"
#include "bullet.hpp"
#include "obstacle.hpp"

class Game
{
public:
  // Constructor
  Game() = default;

  void Start()
  {
    // Start game:
    // Load textures from files
  }

  void LoadLevel()
  {
    // Increment level number
    // Load game objects
    // Draw splash screen
  }

  void Tick()
  {
    // Game main loop:
    // Control game logic depending on game states
  }

  void Draw()
  {
    // Draw objects (with Renderer class)
  }

  void KeyInput(int)
  {
    // Control game logic depending on pressed keys from keyboard
  }

  void Logic()
  {
    // Realisation of game logic
  }

private:
  enum m_stateArray {MENU, LOAD_LEVEL, GAME, FAIL};  // Game states
  m_stateArray m_state = MENU;
  int m_score = 0;
  int m_level = 0;
  int m_menuItem = 0;

  Gun m_gun;
  AlienGroup m_alien;
  std::list<Obstacle> m_obstacle;
  std::list<Bullet> m_bullet;
};