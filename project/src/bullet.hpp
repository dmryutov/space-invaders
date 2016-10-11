#pragma once

#include "game_entity.hpp"

class Bullet: public GameEntity
{
public:
  // Constructor
  Bullet(int, int, bool)
  {
    // Set dimensions and position
  }

  void Move()
  {
    // Get bullet direction and move with GameEntity::Move()
  }

  bool m_fromPlayer;
  bool m_damage = 1;
};
