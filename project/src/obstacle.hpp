#pragma once

#include "game_entity.hpp"

class Obstacle: public GameEntity
{
public:
  // Constructor
  Obstacle(int, int)
  {
    // Set dimensions and position
  }

  int m_health = 10;
};