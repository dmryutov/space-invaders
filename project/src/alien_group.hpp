#pragma once

#include <list>
#include <random>
#include "settings.hpp"
#include "renderer.hpp"
#include "alien.hpp"

class AlienGroup: public GameEntity
{
public:
  // Constructor
  AlienGroup() = default;

  // Functionality
  void Reset()
  {
    // Reset parameters when start new game
    m_speed = 4.5;
    m_shootPossibility = 1.3;
  }

  void Create(int const level)
  {
    // Increase difficulty level by level
    m_speed += 0.5;
    m_shootPossibility += 0.2;
    int health = 1 + level / 15;

    int rowCount = 3;
    int colCount = 10;
    // Alien group dimensions
    float w, h = 70;
    float gap = 1.5;
    float alienWidth = gap * Settings::alienWidth * colCount;
    float alienHeight = gap * Settings::alienHeight * rowCount;
    m_width = alienWidth - (gap - 1) * Settings::alienWidth;
    m_height = alienHeight - (gap - 1) * Settings::alienHeight;

    // Alien group position
    m_position = {(Settings::windowWidth - alienWidth) / 2 + gap * Settings::alienWidth / 2, h};
    
    // Create aliens
    m_alien.clear();
    for (int i = 0; i < rowCount; ++i)
    {
      w = m_position.x();
      for (int j = 0; j < colCount; ++j)
      {
        m_alien.push_back(Alien(w, h, m_speed, health));
        w += gap * Settings::alienWidth;
      }
      h += gap * Settings::alienHeight;
    }
  }

  void Draw(Renderer & renderer)
  {
    for (auto alien : m_alien)
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
    for (auto &alien : m_alien)
      alien.GameEntity::Move(direction);
  }

  void Shoot(std::list<Bullet> & bullet)
  {
    // Shoot logic
    std::random_device rd;
    std::default_random_engine e(rd());
    std::uniform_real_distribution<double> dist(1, 100);

    for (auto & alien : m_alien)
    {
      if (dist(e) < m_shootPossibility)
        alien.Shoot(bullet);
    }
  }

  std::list<Alien> m_alien;
  float m_shootPossibility = 1;
};