#pragma once

#include <list>
#include "settings.hpp"
#include "game_entity.hpp"
#include "bullet.hpp"

class Gun: public GameEntity
{
public:
  // Constructor
  Gun() = default;

  // Functionality
  void Reset()
  {
    // Reset parameters when start new game
    m_health = 3;
    m_speed = 10;
  }

  void Create()
  {
    // Dimensions
    m_width = Settings::gunWidth;
    m_height = Settings::gunHeight;
    // Coords
    m_position = {(Settings::windowWidth - m_width) / 2, Settings::windowHeight - m_height};
  }

  void Shoot(std::list<Bullet> & bullet)
  {
    bullet.push_back(Bullet(m_position.x() + m_width/2, m_position.y(), true));
  }
};