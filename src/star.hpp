#pragma once

#include "settings.hpp"
#include "game_entity.hpp"

class Star: public GameEntity
{
public:
  // Constructor
  Star()
  {
    std::random_device rd;
    std::default_random_engine e(rd());
    std::uniform_real_distribution<float> posX(10, Settings::windowWidth - 10);
    std::uniform_real_distribution<float> posY(10, Settings::windowHeight - 10);
    std::uniform_real_distribution<float> size(4, 10);

    m_width = size(e);
    m_height = m_width;
    m_position = {posX(e), posY(e)};
  }
};
