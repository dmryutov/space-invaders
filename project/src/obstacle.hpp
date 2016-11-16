#pragma once

#include "settings.hpp"
#include "game_entity.hpp"

class Obstacle: public GameEntity
{
public:
  // Operator <<
  friend std::ostream & operator << (std::ostream & os, Obstacle const & obj);

  // Constructor
  Obstacle(int current, int total)
  {
    if (total < 1)
      throw std::invalid_argument("Amount of obstacles should be greater than 0!");

    m_health = Settings::obstacleHealth;
    // Dimensions
    m_width = Settings::obstacleWidth;
    m_height = Settings::obstacleHeight;
    int gap = (Settings::windowWidth - total * m_width) / (total + 1);
    // Coords
    m_position = {(current + 1) * gap + current * m_width, Settings::windowHeight - 100};
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