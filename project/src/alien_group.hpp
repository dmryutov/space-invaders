#pragma once

#include <list>
#include "alien.hpp"

class AlienGroup: public GameEntity
{
public:
  // Constructor
  AlienGroup() = default;

  void Reset() {
    // Reset aliens' parameters when start new game
  }

  void Create() {
    // Set group dimensions
    // Create aliens
  }

  void Move() {
    // Move aliens' group around a circle
  }

  void Shoot(std::list<Bullet> &) {
    // Shoot logic:
    // Decide which alien should shoot (by random)
  }

  std::list<Alien> m_alien;
};