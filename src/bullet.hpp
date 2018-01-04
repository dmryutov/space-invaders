#pragma once

#include "settings.hpp"
#include "game_entity.hpp"

class Bullet: public GameEntity
{
public:
  // Operator <<
  friend std::ostream & operator << (std::ostream & os, Bullet const & obj);

  // Constructor
  Bullet(float x, float y, bool fromPlayer)
  {
    m_width = Settings::bulletWidth;
    m_height = Settings::bulletHeight;
    m_position = {x, y};

    m_fromPlayer = fromPlayer;
    m_speed = Settings::bulletSpeed;
    m_textureIndex = fromPlayer ? 0 : 1;
    m_texture = &Renderer::Instance().m_bulletTexture;
  }

  void Move()
  {
    if (m_fromPlayer)
      GameEntity::Move(GameEntity::MOVE_UP);
    else
      GameEntity::Move(GameEntity::MOVE_DOWN);
  }

  bool m_fromPlayer;
};

inline std::ostream & operator << (std::ostream & os, Bullet const & obj)
{
  os << "Bullet" << ": {"
     << "Position: " << obj.m_position
     << ", Speed: " << obj.m_speed
     << ", FromPlayer: " << obj.m_fromPlayer
     << "}";
  return os;
}
