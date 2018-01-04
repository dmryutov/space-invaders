#pragma once

#include "game_entity.hpp"
#include "sound_manager.hpp"

class Explosion: public GameEntity
{
public:
  Explosion(GameEntity const & obj)
  {
    m_width = std::min(obj.m_width, obj.m_height) * 0.8;
    m_height = m_width;
    m_position = obj.m_position;

    SoundManager::Instance().Play(SoundManager::EXPLOSION);
  }

  int m_frame = 0;
  int m_frameCount = Settings::explosionFrames;
  int m_duration = 0;
};
