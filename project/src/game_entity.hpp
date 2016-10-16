#pragma once

#include "settings.hpp"
#include "box2d.hpp"

class GameEntity
{
public:
  enum MoveDirection {MOVE_LEFT, MOVE_DOWN, MOVE_RIGHT, MOVE_UP};

  // Constructor
  GameEntity() = default;

  // Destructor
  virtual ~GameEntity() = default;

  // Functionality
  void Move(MoveDirection const direction)
  {
    // Move game object
    if (direction == MOVE_LEFT && m_position.x() - m_speed > 0)
      m_position.x() -= m_speed;
    else if (direction == MOVE_RIGHT && m_position.x() + m_speed < Settings::windowWidth)
      m_position.x() += m_speed;
    else if (direction == MOVE_UP && m_position.y() - m_speed > 0)
      m_position.y() -= m_speed;
    else if (direction == MOVE_DOWN && m_position.y() + m_speed < Settings::windowHeight)
      m_position.y() += m_speed;
  }

  Point2D m_position {0, 0};
  float m_width = 1;
  float m_height = 1;
  int m_health = 1;
protected:
  float m_speed = 10;
};