#pragma once

#include <list>
#include <random>
#include "settings.hpp"
#include "ray2d.hpp"
#include "gun.hpp"
#include "alien.hpp"

class AlienGroup: public GameEntity
{
public:
  // Operator <<
  friend std::ostream & operator << (std::ostream & os, AlienGroup const & obj);

  // Constructor
  AlienGroup() = default;

  // Reset parameters when start new game
  void Reset()
  {
    m_speed = Settings::alienSpeed;
    m_shootPossibility = Settings::alienShootPossibility;
  }

  // Reset parameters at each level
  void Create(int const level)
  {
    // Increase difficulty level by level
    m_speed += Settings::alienSpeedInc;
    m_shootPossibility += Settings::alienShootPossibilityInc;

    // Alien group dimensions
    float w, h = 320;
    float gap = 1.5;
    float alienWidth = gap * Settings::alienWidth * Settings::alienColCount;
    float alienHeight = gap * Settings::alienHeight * Settings::alienRowCount;

    m_width = alienWidth - (gap - 1) * Settings::alienWidth;
    m_height = alienHeight - (gap - 1) * Settings::alienHeight;
    m_position = {Settings::windowWidth / 2, h + alienHeight / 2};

    // Create aliens
    std::random_device rd;
    std::default_random_engine e(rd());
    std::uniform_real_distribution<double> dist(0, Settings::alienTextureCount);
    m_aliens.clear();
    for (int i = 0; i < Settings::alienRowCount; ++i)
    {
      w = m_position.x() - (alienWidth - gap * Settings::alienWidth) / 2;
      int texture = dist(e);
      for (int j = 0; j < Settings::alienColCount; ++j)
      {
        m_aliens.push_back(Alien(w, h, m_speed, texture, level));
        w += gap * Settings::alienWidth;
      }
      h += gap * Settings::alienHeight;
    }
  }

  // Move aliens around a circle
  void Move()
  {
    bool q0 = m_position.x() - m_width / 2 - m_speed > 0;  // Left
    bool q1 = m_position.y() - m_height / 2 - m_speed > 250;  // Down
    bool q2 = m_position.x() + m_width / 2 + m_speed < Settings::windowWidth;  // Right
    bool q3 = m_position.y() + m_height / 2 + m_speed < 530; // Up
    MoveDirection direction;

    // Get direction
    if (!q3 && q0)
      direction = Alien::MOVE_LEFT;
    else if (!q0 && q1)
      direction = Alien::MOVE_DOWN;
    else if (!q1 && q2)
      direction = Alien::MOVE_RIGHT;
    else
      direction = Alien::MOVE_UP;

    GameEntity::Move(direction);
    for (auto & alien : m_aliens)
      alien.GameEntity::Move(direction);
  }

  // Aliens shoot logic
  void Shoot(Gun const & gun, std::list<Bullet> & bullets)
  {
    std::random_device rd;
    std::default_random_engine e(rd());
    std::uniform_real_distribution<double> dist(1, 100);

    Box2D gun_box {gun.m_position, gun.m_width, gun.m_height};

    for (auto & alien : m_aliens)
    {
      float x = alien.m_position.x();
      if (Ray2D(x, alien.m_position.y(), x, 0).IntersectSector(gun_box, Settings::alienRayWidth)
          && dist(e) < m_shootPossibility)
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
