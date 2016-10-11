#pragma once

#include <list>
#include "game_entity.hpp"
#include "bullet.hpp"

class Alien: public GameEntity
{
public:
  // Constructor
  Alien(int, int, int)
  {
    // Set speed, dimensions and position
  }

  void Shoot(std::list<Bullet> &)
  {
    // Shoot (add bullet to std::list<Bullet>)
  }

  int m_health = 1;
  int m_score = 10;
};