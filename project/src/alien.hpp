#pragma once

#include <list>
#include "settings.hpp"
#include "game_entity.hpp"
#include "bullet.hpp"

class Alien: public GameEntity
{
public:
  // Operator <<
  friend std::ostream & operator << (std::ostream & os, Alien const & obj);

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
  void Shoot(std::list<Bullet> & bullets)
  {
    bullets.emplace_back(Bullet(m_position.x() + m_width/2, m_position.y() + m_height, false));
  }

  int m_score = 10;
};

inline std::ostream & operator << (std::ostream & os, Alien const & obj)
{
  os << "Alien" << ": {"
     << "Position: " << obj.m_position
     << ", Speed: " << obj.m_speed
     << ", Health: " << obj.m_health
     << "}";
  return os;
}