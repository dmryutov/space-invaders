#pragma once

#include "box2d.hpp"

class GameEntity {
public:
  // Constructor
  GameEntity() = default;

  // Destructor
  virtual ~GameEntity() = default;

  // Move direction
  enum MoveDir {MOVE_LEFT, MOVE_DOWN, MOVE_RIGHT, MOVE_UP};

  void Move(MoveDir dir) {
    // Move game object
  }
protected:
  Box2D m_box;
  int m_speed;
};