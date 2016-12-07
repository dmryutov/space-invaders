#pragma once

#include "settings.hpp"
#include "action_manager.hpp"
#include "renderer.hpp"
#include "gun.hpp"
#include "alien_group.hpp"
#include "bullet.hpp"
#include "obstacle.hpp"
#include "bonus.hpp"
#include "star.hpp"
#include "explosion.hpp"
#include "patterns.hpp"
#include "sound_manager.hpp"

class Game: public Singleton<Game>
{
public:
  using TOnUpdateHandler = std::function<void()>;
  // Operator <<
  friend std::ostream & operator << (std::ostream & os, Game const & obj);

  // Control game logic depending on pressed keys from keyboard
  void KeyInput()
  {
    if (ACTIONS[ActionManager::KEY_UP]) {
      ActionManager::Instance().SingleAction(ActionManager::KEY_UP);
      if (m_state == OPTIONS && Settings::optionItem != 0)
        Settings::optionItem--;
      else if ((m_state == MENU || m_state == FAIL) && m_menuItem != 0)
        m_menuItem--;
    }
    if (ACTIONS[ActionManager::KEY_DOWN]) {
      ActionManager::Instance().SingleAction(ActionManager::KEY_DOWN);
      if ((m_state == MENU && m_menuItem != 2) || (m_state == FAIL && m_menuItem != 1))
        m_menuItem++;
      else if (m_state == OPTIONS && Settings::optionItem != 3)
        Settings::optionItem++;
    }
    if (ACTIONS[ActionManager::KEY_LEFT]) {
      if (m_state == GAME)
        m_gun.Move(GameEntity::MOVE_LEFT);
      else if (m_state == OPTIONS)
      {
        ActionManager::Instance().SingleAction(ActionManager::KEY_LEFT);
        if (Settings::optionItem == 0 && Settings::difficultyItem != 0)
          Settings::difficultyItem--;
        else if (Settings::optionItem == 1 && Settings::resolutionItem != 0)
        {
          Settings::resolutionItem--;
          Settings::ChangeResolution();
        }
        else if (Settings::optionItem == 2 && Settings::gunSkinItem != 0)
          Settings::gunSkinItem--;
      }
    }
    if (ACTIONS[ActionManager::KEY_RIGHT]) {
      if (m_state == GAME)
        m_gun.Move(GameEntity::MOVE_RIGHT);
      else if (m_state == OPTIONS)
      {
        ActionManager::Instance().SingleAction(ActionManager::KEY_RIGHT);
        if (Settings::optionItem == 0 && Settings::difficultyItem != Settings::difficulty.size() - 1)
          Settings::difficultyItem++;
        else if (Settings::optionItem == 1 && Settings::resolutionItem != Settings::resolution.size() - 1)
        {
          Settings::resolutionItem++;
          Settings::ChangeResolution();
        }
        else if (Settings::optionItem == 2 && Settings::gunSkinItem != Settings::gunTextureCount)
          Settings::gunSkinItem++;
      }
    }
    if (ACTIONS[ActionManager::KEY_SHOOT]) {
      if (m_state == GAME)
      {
        if (++m_shootDuration >= m_gun.m_shootDelay)
        {
          m_shootDuration = 0;
          m_gun.Shoot(m_bullets);
        }
      }
    }
    if (ACTIONS[ActionManager::KEY_ENTER]) {
      ActionManager::Instance().SingleAction(ActionManager::KEY_ENTER);
      // Start menu
      if (m_state == MENU)
      {
        if (m_menuItem == 0)
        {
          SoundManager::Instance().Stop(SoundManager::MENU);
          m_state = LOAD_LEVEL;
        }
        else if (m_menuItem == 1)
          m_state = OPTIONS;
        else if (m_menuItem == 2)
          m_exitGame = true;
      }
      // Options menu
      else if (m_state == OPTIONS)
      {
        if (Settings::optionItem == 3)
        {
          Settings::Save();
          Reset();
        }
      }
      // Game over menu
      else if (m_state == FAIL)
      {
        if (m_menuItem == 0)
          Reset();
        else if (m_menuItem == 1)
          m_exitGame = true;
      }
    }
    if (ACTIONS[ActionManager::KEY_PAUSE]) {
      ActionManager::Instance().SingleAction(ActionManager::KEY_PAUSE);
      if (m_state == PAUSE)
        m_state = GAME;
      else if (m_state == GAME)
        m_state = PAUSE;
      Pause();
    }
    if (ACTIONS[ActionManager::KEY_QUIT]) {
      ActionManager::Instance().SingleAction(ActionManager::KEY_QUIT);
      if (m_state == GAME)
      {
        EndGame();
      }
      else
      {
        SoundManager::Instance().Stop(SoundManager::MENU);
        m_exitGame = true;
      }
    }
  }

  // Main game loop. Control game logic depending on game states
  void Tick()
  {
    int duration = GetTickDuration();

    switch (m_state)
    {
      case MENU:
        Renderer::Instance().DrawMenu(m_menuItem);
        m_gun.Reset();
        m_alien->Reset();
        break;
      case OPTIONS:
        Renderer::Instance().DrawOptions();
        break;
      case LOAD_LEVEL:
        LoadLevel();
        m_loadLevelDuration += duration;
        break;
      case GAME:
        Draw();
        Logic();
        if (m_shootDuration > 0)
          m_shootDuration += duration;
        if (m_weaponDuration > 0)
          m_weaponDuration++;
        if (m_shieldDuration > 0)
          m_shieldDuration ++;
        for (auto & explosion : m_explosions)
          explosion.m_duration += duration;
        break;
      case PAUSE:
        Draw();
        break;
      case FAIL:
        Renderer::Instance().DrawEndMenu(m_score, m_menuItem);
        break;
    }
    KeyInput();

    LOG(LOG_DEBUG) << *this;
  }

  void Reset()
  {
    m_score = 0;
    m_level = 0;
    m_state = MENU;
    SoundManager::Instance().Play(SoundManager::MENU, true);
  }

  void Pause()
  {
    if (m_updateHandler != nullptr)
      m_updateHandler();
  }

  void SetUpdateHandler(TOnUpdateHandler const & handler)
  {
    m_updateHandler = handler;
  }

  bool m_exitGame = false;

private:
  friend class Singleton<Game>;

  // Constructor
  Game() = default;

  void LoadLevel()
  {
    // Draw load screen
    Renderer::Instance().DrawLevelLoad(m_level+1, m_loadLevelDuration);
    if (Renderer::Instance().m_loadLevelPosition >= Settings::windowHeight + Settings::loadLevelEndPause) {
      m_loadLevelDuration = 0;
      Renderer::Instance().m_loadLevelPosition = 0;

      m_level++;
      m_state = GAME;
      // Generate stars
      m_stars.clear();
      for (int i = 0; i < Settings::starCount; ++i)
        m_stars.emplace_back(Star());

      // Delete bullets
      m_bullets.clear();
      // Delete explosions
      m_explosions.clear();
      // Load gun
      m_gun.Create();
      // Load aliens
      m_alien->Create(m_level);

      // Load obstacles
      try
      {
        std::random_device rd;
        std::default_random_engine e(rd());
        std::uniform_int_distribution<int> dist(0, Settings::obstacleTextureCount-1);
        int texture = dist(e);

        m_obstacles.clear();
        for (int i = 0; i < Settings::obstacleCount; ++i)
          m_obstacles.emplace_back(i, texture, Settings::obstacleCount);
      }
      catch (std::exception const & ex)
      {
        LOG(LOG_ERROR) << ex.what();
      }

      // Set gun pause handler
      SetUpdateHandler([this]()
      {
        m_gun.m_pause = (m_state == PAUSE);
      });
    }
  }

  // Draw game objects
  void Draw()
  {
    for (auto const & star : m_stars)
      Renderer::Instance().DrawBackground(star, (m_state == PAUSE));

    for (auto const & bullet : m_bullets)
      Renderer::Instance().Draw(bullet);
    for (auto const & alien : m_alien->m_aliens)
      Renderer::Instance().Draw(alien);
    for (auto const & obstacle : m_obstacles)
      Renderer::Instance().Draw(obstacle);
    for (auto const & explosion : m_explosions)
      Renderer::Instance().DrawExplosion(explosion);
    Renderer::Instance().DrawGun(m_gun, m_gun.m_shield);

    if (m_bonus != nullptr)
      Renderer::Instance().Draw(*m_bonus);

    // Draw interface
    Renderer::Instance().DrawPanel(m_score, m_level, m_gun.m_health, m_shieldDuration>0, m_weaponDuration>0);
  }

  // Main game logic
  void Logic()
  {
    // Move aliens
    m_alien->Move();
    // Shoot aliens
    m_alien->Shoot(m_gun, m_bullets);
    // Move bonus
    if (m_bonus != nullptr)
      m_bonus->Move();
    // Create bonus
    if(m_bonusDuration++ >= Settings::bonusDelay)
    {
      m_bonus = new Bonus();
      m_bonusDuration = 0;
    }
    if (m_shieldDuration >= Settings::bonusShieldDuration)
    {
      m_shieldDuration = 0;
      m_gun.m_shield = false;
    }
    if (m_weaponDuration >= Settings::bonusWeaponDuration)
    {
      m_weaponDuration = 0;
      m_gun.m_shootDelay = Settings::gunShootDelay;
    }

    try
    {
      // Move bullets
      for (auto bullet = m_bullets.begin(); bullet != m_bullets.end(); )
      {
        Box2D bulletBox(bullet->m_position, bullet->m_width, bullet->m_height);
        bool skip = false;

        // Hit obstacle
        for (auto obstacle = m_obstacles.begin(); obstacle != m_obstacles.end(); )
        {
          if (bulletBox.IntersectBox(Box2D(obstacle->m_position, obstacle->m_width, obstacle->m_height)))
          {
            obstacle->GetDamage();
            bullet = m_bullets.erase(bullet);
            // Kill obstacle
            if (obstacle->m_health == 0)
            {
              m_explosions.emplace_back(Explosion(*obstacle));
              obstacle = m_obstacles.erase(obstacle);
            }
            skip = true;
            break;
          }
          else
          {
            ++obstacle;
          }
        }
        if (skip) continue;

        // Hit aliens
        for (auto alien = m_alien->m_aliens.begin(); alien != m_alien->m_aliens.end(); )
        {
          if (bullet->m_fromPlayer && bulletBox.IntersectBox(Box2D(alien->m_position, alien->m_width, alien->m_height)))
          {
            alien->m_health--;
            bullet = m_bullets.erase(bullet);
            // Kill alien
            if (alien->m_health == 0)
            {
              m_explosions.emplace_back(Explosion(*alien));
              m_score += alien->m_score;
              alien = m_alien->m_aliens.erase(alien);
            }
            skip = true;
            break;
          }
          else
          {
            ++alien;
          }
        }
        if (skip) continue;

        // Bullet is out of screen
        if (bullet->m_position.y() - bullet->m_height / 2 < 1 || bullet->m_position.y() + bullet->m_height / 2 > Settings::windowHeight - 90)
          bullet = m_bullets.erase(bullet);
        // Hit gun
        else if (!bullet->m_fromPlayer && bulletBox.IntersectBox(Box2D(m_gun.m_position, m_gun.m_width, m_gun.m_height)))
        {
          m_gun.ChangeHealth(true);
          bullet = m_bullets.erase(bullet);
        }
        // Move bullets
        else
        {
          bullet->Move();
          ++bullet;
        }
      }

      // Delete explosions
      for (auto explosion = m_explosions.begin(); explosion != m_explosions.end(); )
      {
        if (explosion->m_duration > Settings::explosionSpeed)
        {
          explosion->m_frame++;
          explosion->m_duration = 0;
        }
        if (explosion->m_frame > explosion->m_frameCount)
          explosion = m_explosions.erase(explosion);
        else
          ++explosion;
      }

      // Hit bonus
      if(m_bonus != nullptr)
      {
        Box2D bonusBox(m_bonus->m_position, m_bonus->m_width, m_bonus->m_height);

        if (bonusBox.IntersectBox(Box2D(m_gun.m_position, m_gun.m_width, m_gun.m_height)))
        {
          switch (m_bonus->GetType())
          {
            case Bonus::HEALTH:
              m_gun.ChangeHealth(false);

              LOG(LOG_DEBUG) << "Bonus: Health - " + std::to_string(m_gun.m_health);
              break;
            case Bonus::SHIELD:
              m_shieldDuration++;
              m_gun.m_shield = true;

              LOG(LOG_DEBUG) << "Bonus: Shield - " + std::to_string(m_gun.m_shield);
              break;
            case Bonus::WEAPON:
              m_weaponDuration++;
              m_gun.m_shootDelay = Settings::gunShootBonusDelay;

              LOG(LOG_DEBUG) << "Bonus: Weapon - " + std::to_string(m_gun.m_shootDelay);
              break;
          }
          if (m_bonus != nullptr)
          {
            delete m_bonus;
            m_bonus = nullptr;
          }
          SoundManager::Instance().Play(SoundManager::BONUS);
        }
        // Bonus is out of screen
        if (m_bonus != nullptr && m_bonus->m_position.y() - m_bonus->m_height / 2 < 1)
        {
          delete m_bonus;
          m_bonus = nullptr;
        }
      }
    }
    catch (...)
    {
      LOG(LOG_ERROR) << "Segmentation fault while processing game objects!";
    }

    // Change game state
    if (m_alien->m_aliens.size() == 0)
    {
      SoundManager::Instance().Stop(SoundManager::SHOOT);
      SoundManager::Instance().Stop(SoundManager::EXPLOSION);
      SoundManager::Instance().Play(SoundManager::WIN);

      m_state = LOAD_LEVEL;
      if (m_bonus != nullptr)
      {
        delete m_bonus;
        m_bonus = nullptr;
      }
    }
    else if (m_gun.m_health <= 0)
      EndGame();
  }

  void EndGame()
  {
    m_state = FAIL;
    Settings::highScore = std::max(m_score, Settings::highScore);
    Settings::Save();
    SoundManager::Instance().Stop(SoundManager::SHOOT);
    SoundManager::Instance().Stop(SoundManager::EXPLOSION);
    SoundManager::Instance().Play(SoundManager::FAIL);
  }

  // Get duration between ticks
  int GetTickDuration()
  {
    static std::chrono::time_point<std::chrono::steady_clock> lastCallTimestamp = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastCallTimestamp);
    lastCallTimestamp = std::chrono::steady_clock::now();
    return duration.count();
  }

  enum m_gameStates {MENU, OPTIONS, LOAD_LEVEL, GAME, PAUSE, FAIL};
  m_gameStates m_state = MENU;
  int m_score = 0;
  int m_level = 0;
  int m_menuItem = 0;

  Gun m_gun;
  std::unique_ptr<AlienGroup> m_alien = Settings::factory.Create<AlienGroup>();
  std::list<Obstacle> m_obstacles;
  std::list<Bullet> m_bullets;
  std::list<Star> m_stars;
  std::list<Explosion> m_explosions;
  Bonus * m_bonus = nullptr;

  int m_shootDuration = 0;
  int m_loadLevelDuration = 0;
  int m_bonusDuration = 0;
  int m_shieldDuration = 0;
  int m_weaponDuration = 0;
  TOnUpdateHandler m_updateHandler;
};

inline std::ostream & operator << (std::ostream & os, Game const & obj)
{
  os << "Game" << ": {"
     << "Score: " << obj.m_score
     << ", Level: " << obj.m_level
     << ", State: " << obj.m_state
     << ", Gun: " << obj.m_gun
     << ", AlienGroup: " << *(obj.m_alien)
     << ", Bullet: " << obj.m_bullets
     << ", Obstacle: " << obj.m_obstacles
     << "}";
  return os;
}
