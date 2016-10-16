#pragma once

#include "settings.hpp"
#include "renderer.hpp"
#include "gun.hpp"
#include "alien_group.hpp"
#include "bullet.hpp"
#include "obstacle.hpp"

class Game
{
public:
  // Constructor
  Game() = default;

  // Functionality
  void Start()
  {
    // Load textures from .bmp
  }

  void KeyInput(int key)
  {
    // Control game logic depending on pressed keys from keyboard
    switch (key)
    {
      case 'w': case 'W':
        if (m_menuItem != 0)
          m_menuItem--;
        break;
      case 's': case 'S':
        if (m_menuItem != 1)
          m_menuItem++;
        break;
      case 'a': case 'A':
        m_gun.Move(GameEntity::MOVE_LEFT);
        break;
      case 'd': case 'D':
        m_gun.Move(GameEntity::MOVE_RIGHT);
        break;
      case 32:  // Space
        m_gun.Shoot(m_bullet);
        break;
      case 13:  // Enter
        // Start menu
        if (m_state == MENU)
        {
          if (m_menuItem == 0)
            m_state = LOAD_LEVEL;
          else if (m_menuItem == 1)
            exit(0);
        }
        // Game over menu
        else if (m_state == FAIL)
        {
          if (m_menuItem == 0)
            m_state = MENU;
          else if (m_menuItem == 1)
            exit(0);
          break;
        }
        break;
      case 27: case 113:  // Esc, q
        exit(0);
        break;
    }
  }

  void Tick()
  {
    // Game main loop. Control game logic depending on game states
    switch (m_state)
    {
      case MENU:
        m_renderer.DrawMenu(m_menuItem);
        m_gun.Reset();
        m_alien.Reset();
        break;
      case LOAD_LEVEL:
        LoadLevel();
        break;
      case GAME:
        Draw();
        Logic();
        break;
      case FAIL:
        m_renderer.DrawEndMenu(m_score, m_menuItem);
        break;
    }
  }

private:
  void LoadLevel()
  {
    m_level++;
    m_state = GAME;
    // Delete bullets
    m_bullet.clear();
    // Load gun
    m_gun.Create();
    // Load aliens
    m_alien.Create(m_level);
    // Load obstacles
    int obstacleCount = 3;
    for (int i = 0; i < obstacleCount; ++i)
      m_obstacle.push_back(Obstacle(i, obstacleCount));

    // Draw load screen
    m_renderer.DrawLevelLoad(m_level);
  }

  void Draw()
  {
    // Draw objects
    m_renderer.DrawPanel(m_score, m_level, m_gun.m_health);
    for (auto bullet : m_bullet)
      m_renderer.Draw(bullet);
    for (auto obstacle : m_obstacle)
      m_renderer.Draw(obstacle);
    m_renderer.Draw(m_gun);
    m_alien.Draw(m_renderer);
  }

  void Logic()
  {
    // Move aliens
    m_alien.Move();
    // Shoot
    m_alien.Shoot(m_bullet);


    /*// Move gun bullets
    for (auto bullet = m_bullet.begin(); bullet != m_bullet.end(); )
    {
      Box2D bulletBox(bullet->m_position, bullet->m_width, bullet->m_height);
      // Out of screen
      if (bullet->m_position.y() < 70 || bullet->m_position.y() + bullet->m_height > Settings::windowHeight - 20)
        m_bullet.erase(bullet++);
      // Kill gun
      else if (!bullet->m_fromPlayer && bulletBox.IntersectBox(Box2D(m_gun.m_position, m_gun.m_width, m_gun.m_height)))
      {
        m_gun.m_health--;
        m_bullet.erase(bullet++);
      }
      // Move bullets
      else
      {
        bullet->Move();
        ++bullet;
      }
    }

    for (auto obstacle = m_obstacle.begin(); obstacle != m_obstacle.end(); )
    {
      for (auto bullet = m_bullet.begin(); bullet != m_bullet.end(); )
      {
        Box2D bulletBox(bullet->m_position, bullet->m_width, bullet->m_height);
        // Kill obstacle
        if (bulletBox.IntersectBox(Box2D(obstacle->m_position, obstacle->m_width, obstacle->m_height)))
        {
          obstacle->m_health--;
          m_bullet.erase(bullet++);
          if (obstacle->m_health == 0)
            m_obstacle.erase(obstacle++);
        }
        else
          ++bullet;
      }
      ++obstacle;
    }

    for (auto alien = m_alien.m_alien.begin(); alien != m_alien.m_alien.end(); )
    {
      for (auto bullet = m_bullet.begin(); bullet != m_bullet.end(); )
      {
        Box2D bulletBox(bullet->m_position, bullet->m_width, bullet->m_height);
        // Kill aliens
        if (bullet->m_fromPlayer && bulletBox.IntersectBox(Box2D(alien->m_position, alien->m_width, alien->m_height)))
        {
          alien->m_health--;
          m_bullet.erase(bullet++);
          if (alien->m_health == 0)
          {
            m_score += alien->m_score;          
            m_alien.m_alien.erase(alien++);
          }
        }
        else
          ++bullet;
      }
      ++alien;
    }*/

    // Move gun bullets
    for (auto bullet = m_bullet.begin(); bullet != m_bullet.end(); )
    {
      Box2D bulletBox(bullet->m_position, bullet->m_width, bullet->m_height);
      bool skip = false;

      // Kill obstacle
      for (auto obstacle = m_obstacle.begin(); obstacle != m_obstacle.end(); )
      {
        if (bulletBox.IntersectBox(Box2D(obstacle->m_position, obstacle->m_width, obstacle->m_height)))
        {
          obstacle->m_health--;
          m_bullet.erase(bullet++);
          if (obstacle->m_health == 0)
            m_obstacle.erase(obstacle++);
          skip = true;
          break;
        }
        else
          ++obstacle;
      }
      if (skip) continue;

      // Kill aliens
      for (auto alien = m_alien.m_alien.begin(); alien != m_alien.m_alien.end(); )
      {
        if (bullet->m_fromPlayer && bulletBox.IntersectBox(Box2D(alien->m_position, alien->m_width, alien->m_height)))
        {
          alien->m_health--;
          m_bullet.erase(bullet++);
          if (alien->m_health == 0)
          {
            m_score += alien->m_score;
            m_alien.m_alien.erase(alien++);
          }
          skip = true;
          break;
        }
        else
          ++alien;
      }
      if (skip) continue;

      // Out of screen
      if (bullet->m_position.y() < 70 || bullet->m_position.y() + bullet->m_height > Settings::windowHeight - 20)
        m_bullet.erase(bullet++);
      // Kill gun
      else if (!bullet->m_fromPlayer && bulletBox.IntersectBox(Box2D(m_gun.m_position, m_gun.m_width, m_gun.m_height)))
      {
        m_gun.m_health--;
        m_bullet.erase(bullet++);
      }
      // Move bullets
      else
      {
        bullet->Move();
        ++bullet;
      }
    }


    // Change game state
    if (m_alien.m_alien.size() == 0)
      m_state = LOAD_LEVEL;
    else if (m_gun.m_health <= 0)
      m_state = FAIL;
  }

  enum m_stateArray {MENU, LOAD_LEVEL, GAME, FAIL};  // Game states
  m_stateArray m_state = MENU;
  int m_score = 0;
  int m_level = 0;
  int m_menuItem = 0;

  Renderer m_renderer;
  Gun m_gun;
  AlienGroup m_alien;
  std::list<Obstacle> m_obstacle;
  std::list<Bullet> m_bullet;
};