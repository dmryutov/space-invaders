#pragma once

#include <list>
#include <random>
#include "settings.hpp"
#include "ray2d.hpp"
#include "renderer.hpp"
#include "gun.hpp"
#include "alien.hpp"

class AlienGroup: public GameEntity
{
public:
  // Operator <<
  friend std::ostream & operator << (std::ostream & os, AlienGroup const & obj);

  // Constructor
  AlienGroup() = default;

  // Functionality
  void Reset()
  {
    // Reset parameters when start new game
    m_speed = Settings::alienSpeed;
    m_shootPossibility = Settings::alienShootPossibility;
  }

  void Create(int const level)
  {
    // Increase difficulty level by level
    m_speed += Settings::alienSpeedInc;
    m_shootPossibility += Settings::alienShootPossibilityInc;
    int health = 1 + level / Settings::alienHealthInc;

    // Alien group dimensions
    float w, h = 70;
    float gap = 1.5;
    float alienWidth = gap * Settings::alienWidth * Settings::alienCol;
    float alienHeight = gap * Settings::alienHeight * Settings::alienRow;
    m_width = alienWidth - (gap - 1) * Settings::alienWidth;
    m_height = alienHeight - (gap - 1) * Settings::alienHeight;

    // Alien group position
    m_position = {(Settings::windowWidth - alienWidth) / 2 + gap * Settings::alienWidth / 2, h};
    
    // Create aliens
    m_aliens.clear();
    for (int i = 0; i < Settings::alienRow; ++i)
    {
      w = m_position.x();
      for (int j = 0; j < Settings::alienCol; ++j)
      {
        m_aliens.push_back(Alien(w, h, m_speed, health));
        w += gap * Settings::alienWidth;
      }
      h += gap * Settings::alienHeight;
    }
  }

  void Draw(Renderer & renderer)
  {
    for (auto const & alien : m_aliens)
      renderer.Draw(alien);
  }

  void Move()
  {
    // Move aliens' group around a circle
    bool q0 = m_position.x() - m_speed > 0;
    bool q1 = m_position.y() + m_height + m_speed < 280;
    bool q2 = m_position.x() + m_width + m_speed < Settings::windowWidth;
    bool q3 = m_position.y() - m_speed > 70;
    MoveDirection direction;

    if (!q3 && q0)
      direction = Alien::MOVE_LEFT;
    else if (!q0 && q1)
      direction = Alien::MOVE_DOWN;
    else if (!q1 && q2)
      direction = Alien::MOVE_RIGHT;
    else if (!q2 && q3)
      direction = Alien::MOVE_UP;

    GameEntity::Move(direction);
    for (auto & alien : m_aliens)
      alien.GameEntity::Move(direction);
  }

  void Shoot(Gun const & gun, std::list<Bullet> & bullets)
  {
    // Shoot logic
    std::random_device rd;
    std::default_random_engine e(rd());
    std::uniform_real_distribution<double> dist(1, 100);

    Box2D gun_box {gun.m_position, gun.m_width, gun.m_height};

    for (auto & alien : m_aliens)
    {
      float x = alien.m_position.x() + alien.m_width / 2;
      float y = alien.m_position.y();

      if (Ray2D(x, y, x, Settings::windowHeight).IntersectSector(gun_box, 40) && dist(e) < m_shootPossibility)
        alien.Shoot(bullets);
    }
  }

  std::list<Alien> m_aliens;
  float m_shootPossibility = 1;
};

inline std::ostream & operator << (std::ostream & os, AlienGroup const & obj)
{
  os << "AlienGroup" << ": {"
     << "Position: " << obj.m_position
     << ", Speed: " << obj.m_speed
     << ", Health: " << obj.m_health
     << ", ShootPossibility: " << obj.m_shootPossibility
     << ", Alien: " << obj.m_aliens
     << "}";
  return os;
}