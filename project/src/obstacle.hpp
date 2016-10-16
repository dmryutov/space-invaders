#pragma once

#include "settings.hpp"
#include "game_entity.hpp"

class Obstacle: public GameEntity
{
public:
  // Constructor
  Obstacle(int current, int total)
  {
    m_health = 10;
    // Dimensions
    m_width = Settings::obstacleWidth;
    m_height = Settings::obstacleHeight;
    int gap = (Settings::windowWidth - total * m_width) / (total + 1);
    // Coords
    m_position = {(current + 1) * gap + current * m_width, Settings::windowHeight - 100};
  }
};