#pragma once

#include "settings.hpp"
#include "renderer.hpp"
#include "box2d.hpp"

class GameEntity
{
public:
  enum MoveDirection {MOVE_LEFT, MOVE_DOWN, MOVE_RIGHT, MOVE_UP};

  // Constructor
  GameEntity() = default;

  // Destructor
  virtual ~GameEntity() = default;

  // Move game objects
  void Move(MoveDirection const direction)
  {
    if (m_pause)
      return;
    if (direction == MOVE_LEFT)
      m_position.x() -= std::min(m_speed, m_position.x() - m_width / 2);
    else if (direction == MOVE_RIGHT)
      m_position.x() += std::min(m_speed, Settings::windowWidth - m_position.x() - m_width / 2);
    else if (direction == MOVE_UP)
      m_position.y() += std::min(m_speed, Settings::windowHeight - m_position.y() - m_height / 2);
    else if (direction == MOVE_DOWN)
      m_position.y() -= std::min(m_speed, m_position.y() - m_height / 2);
  }

  Point2D m_position {0, 0};
  float m_width = 1;
  float m_height = 1;
  int m_health = 1;
  int m_textureIndex = 0;
  std::vector<QOpenGLTexture *> * m_texture;
  bool m_pause = false;
protected:
  float m_speed = 10;
};
