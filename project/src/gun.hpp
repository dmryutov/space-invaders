#pragma once

#include <list>
#include <random>
#include "settings.hpp"
#include "sound_manager.hpp"
#include "game_entity.hpp"
#include "bullet.hpp"

class Gun: public GameEntity
{
public:
  // Operator <<
  friend std::ostream & operator << (std::ostream & os, Gun const & obj);

  // Constructor
  Gun() = default;

  // Reset parameters when start new game
  void Reset()
  {
    m_health = Settings::gunHealth;
    m_speed = Settings::gunSpeed;
    m_texture = &Renderer::Instance().m_gunTexture["good"];
    if (Settings::gunSkinItem == 0)
    {
      std::random_device rd;
      std::default_random_engine e(rd());
      std::uniform_real_distribution<double> texture(0, Settings::gunTextureCount);
      m_textureIndex = texture(e);
    }
    else
    {
      m_textureIndex = Settings::gunSkinItem - 1;
    }
  }

  // Reset parameters at each level
  void Create()
  {
    m_width = Settings::gunWidth;
    m_height = Settings::gunHeight;
    m_position = {Settings::windowWidth / 2, m_height / 2 + 15};
    m_shootDelay = Settings::gunShootDelay;
  }

  // Decrease health after bullet hit or increase after bonus
  void ChangeHealth(bool hit)
  {
    if (hit && !m_shield)
      m_health--;
    else if (!hit && m_health < 5)
      m_health++;

    if (m_health <= Settings::gunHealth / 2)
      m_texture = &Renderer::Instance().m_gunTexture["bad"];
    else
      m_texture = &Renderer::Instance().m_gunTexture["good"];
  }

  void Shoot(std::list<Bullet> & bullets)
  {
    if (!m_pause)
    {
      SoundManager::Instance().Play(SoundManager::SHOOT);
      bullets.emplace_back(m_position.x(), m_position.y() + m_height / 2, true);
    }
  }

  int m_shootDelay;
  bool m_shield;
};

inline std::ostream & operator << (std::ostream & os, Gun const & obj)
{
  os << "Gun" << ": {"
     << "Position: " << obj.m_position
     << ", Health: " << obj.m_health
     << ", Speed: "<< obj.m_speed
     << "}";
  return os;
}
