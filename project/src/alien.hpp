#pragma once

#include <list>
#include "settings.hpp"
#include "game_entity.hpp"
#include "bullet.hpp"

class Alien: public GameEntity
{
public:
  // Constructor
  Alien(float x, float y, int speed, int health)
  {
    m_speed = speed;
    m_health = health;
    // Dimensions
    m_width = Settings::alienWidth;
    m_height = Settings::alienHeight;
    // Coords
    m_position = {x, y};
  }

  // Functionality
  void Shoot(std::list<Bullet> & bullet)
  {
    bullet.push_back(Bullet(m_position.x() + m_width/2, m_position.y() + m_height, false));
  }

  int m_score = 10;
};