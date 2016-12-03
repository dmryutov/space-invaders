#pragma once

#include "settings.hpp"
#include "game_entity.hpp"

class Obstacle: public GameEntity
{
public:
  // Operator <<
  friend std::ostream & operator << (std::ostream & os, Obstacle const & obj);

  // Constructor
  Obstacle(int current, int texture, int total)
  {
    if (total < 1)
      throw std::invalid_argument("Amount of obstacles should be greater than 0!");

    m_health = Settings::obstacleHealth;
    m_textureIndex = texture;
    m_texture = &Renderer::Instance().m_obstacleTexture["good"];

    m_width = Settings::obstacleWidth;
    m_height = Settings::obstacleHeight;
    int gap = (Settings::windowWidth - total * m_width) / (total + 1);
    m_position = {(current+1) * gap + current * m_width + m_width / 2, 130};
  }

  // Get damage after bullet hit
  void GetDamage()
  {
    m_health--;
    if (m_health <= Settings::obstacleHealth / 2)
      m_texture = &Renderer::Instance().m_obstacleTexture["bad"];
    else if (m_health <= Settings::obstacleHealth * 2 / 3)
      m_texture = &Renderer::Instance().m_obstacleTexture["mid"];
  }
};

inline std::ostream & operator << (std::ostream & os, Obstacle const & obj)
{
  os << "Obstacle" << ": {"
     << "Position: " << obj.m_position
     << ", Health: " << obj.m_health
     << "}";
  return os;
}
