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
  Alien(float x, float y, int speed, int texture, int level)
  {
    m_width = Settings::alienWidth;
    m_height = Settings::alienHeight;
    m_position = {x, y};

    m_health = Settings::alienHealth + level / Settings::alienHealthInc;
    m_speed = speed;
    m_textureIndex = texture;
    m_texture = &Renderer::Instance().m_alienTexture;
  }

  void Shoot(std::list<Bullet> & bullets)
  {
    bullets.emplace_back(m_position.x(), m_position.y() - m_height / 2, false);
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
