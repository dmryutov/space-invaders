#pragma once

#include <list>
#include "game_entity.hpp"
#include "bullet.hpp"

class Gun: public GameEntity
{
public:
  // Constructor
  Gun() = default;

  void Reset()
  {
    // Reset gun's health and speed when start new game
  }

  void Create(int const)
  {
    // Set dimensions and position
  }

  void Shoot(std::list<Bullet> &)
  {
    // Shoot (add bullet to std::list<Bullet>)
  }

  int m_health = 3;
};