#pragma once

#include <list>
#include "settings.hpp"
#include "game_entity.hpp"
#include "bullet.hpp"

class Gun: public GameEntity
{
public:
  // Operator <<
  friend std::ostream & operator << (std::ostream & os, Gun const & obj);

  // Constructor
  Gun() = default;

  // Functionality
  void Reset()
  {
    // Reset parameters when start new game
    m_health = Settings::gunHealth;
    m_speed = Settings::gunSpeed;
  }

  void Create()
  {
    // Dimensions
    m_width = Settings::gunWidth;
    m_height = Settings::gunHeight;
    // Coords
    m_position = {(Settings::windowWidth - m_width) / 2, Settings::windowHeight - m_height};
  }

  void Shoot(std::list<Bullet> & bullets)
  {
    if (!m_pause)
      bullets.emplace_back(Bullet(m_position.x() + m_width / 2, m_position.y(), true));
  }
};

inline std::ostream & operator << (std::ostream & os, Gun const & obj)
{
  os << "Gun" << ": {"
     << "Position: " << obj.m_position
     << ", Health: " << obj.m_health
     << ", Speed: "<< obj.m_speed
     << "}";
  return os;
}