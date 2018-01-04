#pragma once

#include <random>
#include "game_entity.hpp"

class Bonus: public GameEntity
{
public:
  enum Types {HEALTH, SHIELD, WEAPON};

  // Constructor
  Bonus()
  {
    std::random_device rd;
    std::default_random_engine e(rd());
    std::uniform_int_distribution<int> type(0, Settings::bonusTextureCount - 1);
    std::uniform_real_distribution<float> posX(20, Settings::windowWidth - 20);
    float posY = 590;

    m_width = Settings::bonusWidth;
    m_height = Settings::bonusHeight;
    m_position = {posX(e), posY};

    m_speed = Settings::bonusSpeed;
    m_texture = &Renderer::Instance().m_bonusTexture;
    m_textureIndex = type(e);
  }

  void Move()
  {
    GameEntity::Move(GameEntity::MOVE_DOWN);
  }

  int GetType() const { return m_textureIndex; }
};
