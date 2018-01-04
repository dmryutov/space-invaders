#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <vector>
#include <unordered_map>
#include "settings.hpp"
#include "textured_rect.hpp"
#include "game_entity.hpp"
#include "explosion.hpp"

class Renderer: public Singleton<Renderer>
{
public:
  void Init(QOpenGLFunctions * glWidget)
  {
    auto & res = Settings::resolution[Settings::resolutionItem];
    m_screenSize.setWidth(res.first);
    m_screenSize.setHeight(res.second);

    m_texturedRect = new TexturedRect();
    m_texturedRect->Initialize(glWidget);

    // Load textures
    for (int i = 1; i <= Settings::gunTextureCount; ++i)
    {
      m_gunTexture["good"].emplace_back(new QOpenGLTexture(QImage(":/data/models/gun/good"+ QString::number(i) +".png")));
      m_gunTexture["bad"].emplace_back(new QOpenGLTexture(QImage(":/data/models/gun/bad"+ QString::number(i) +".png")));
      m_gunTexture["good"][i-1]->setMagnificationFilter(QOpenGLTexture::Nearest);
      m_gunTexture["bad"][i-1]->setMagnificationFilter(QOpenGLTexture::Nearest);
    }
    for (int i = 1; i <= Settings::alienTextureCount; ++i)
    {
      m_alienTexture.emplace_back(new QOpenGLTexture(QImage(":/data/models/alien/alien"+ QString::number(i) +".png")));
      m_alienTexture[i-1]->setMagnificationFilter(QOpenGLTexture::Nearest);
    }
    for (int i = 1; i <= Settings::bulletTextureCount; ++i)
    {
      m_bulletTexture.emplace_back(new QOpenGLTexture(QImage(":/data/models/bullet/bullet"+ QString::number(i) +".png")));
      m_bulletTexture[i-1]->setMagnificationFilter(QOpenGLTexture::Nearest);
    }
    for (int i = 1; i <= Settings::obstacleTextureCount; ++i)
    {
      m_obstacleTexture["good"].emplace_back(new QOpenGLTexture(QImage(":/data/models/obstacle/good"+ QString::number(i) +".png")));
      m_obstacleTexture["mid"].emplace_back(new QOpenGLTexture(QImage(":/data/models/obstacle/mid"+ QString::number(i) +".png")));
      m_obstacleTexture["bad"].emplace_back(new QOpenGLTexture(QImage(":/data/models/obstacle/bad"+ QString::number(i) +".png")));
      m_obstacleTexture["good"][i-1]->setMagnificationFilter(QOpenGLTexture::Nearest);
      m_obstacleTexture["mid"][i-1]->setMagnificationFilter(QOpenGLTexture::Nearest);
      m_obstacleTexture["bad"][i-1]->setMagnificationFilter(QOpenGLTexture::Nearest);
    }
    for (int i = 1; i <= Settings::bonusTextureCount; ++i)
    {
      m_bonusTexture.emplace_back(new QOpenGLTexture(QImage(":/data/models/bonus/bonus"+ QString::number(i) +".png")));
      m_bonusTexture[i-1]->setMagnificationFilter(QOpenGLTexture::Nearest);
    }

    m_menuAlienTexture = new QOpenGLTexture(QImage(":/data/models/menuAlien.png"));
    m_menuAlienTexture->setMagnificationFilter(QOpenGLTexture::Nearest);
    m_heartTexture = new QOpenGLTexture(QImage(":/data/models/heart.png"));
    m_heartTexture->setMagnificationFilter(QOpenGLTexture::Nearest);
    m_starTexture = new QOpenGLTexture(QImage(":/data/models/star.png"));
    m_starTexture->setMagnificationFilter(QOpenGLTexture::Nearest);
    m_questionTexture = new QOpenGLTexture(QImage(":/data/models/question.png"));
    m_questionTexture->setMagnificationFilter(QOpenGLTexture::Nearest);
    m_shieldTexture = new QOpenGLTexture(QImage(":/data/models/bonus/shield.png"));
    m_shieldTexture->setMagnificationFilter(QOpenGLTexture::Nearest);
    m_explosionTexture = new QOpenGLTexture(QImage(":/data/models/explosion.png"));
    m_explosionTexture->setMagnificationFilter(QOpenGLTexture::Nearest);
  }

  void Delete()
  {
    for (size_t i = 0; i < m_gunTexture["good"].size(); ++i)
    {
        delete m_gunTexture["good"][i];
        delete m_gunTexture["bad"][i];
    }
    for (size_t i = 0; i < m_alienTexture.size(); ++i)
    {
        delete m_alienTexture[i];
    }
    for (size_t i = 0; i < m_bulletTexture.size(); ++i)
    {
        delete m_bulletTexture[i];
    }
    for (size_t i = 0; i < m_obstacleTexture["good"].size(); ++i)
    {
        delete m_obstacleTexture["good"][i];
        delete m_obstacleTexture["mid"][i];
        delete m_obstacleTexture["bad"][i];
    }
    for (size_t i = 0; i < m_bonusTexture.size(); ++i)
    {
        delete m_bonusTexture[i];
    }
    delete m_menuAlienTexture;
    delete m_heartTexture;
    delete m_starTexture;
    delete m_questionTexture;
    delete m_shieldTexture;
    delete m_explosionTexture;

    delete m_texturedRect;

    m_gunTexture.clear();
    m_alienTexture.clear();
    m_bulletTexture.clear();
    m_obstacleTexture.clear();
  }

  void Blending(bool on)
  {
    if (on)
    {
      glEnable(GL_CULL_FACE);
      glEnable(GL_BLEND);
    }
    else
    {
      glDisable(GL_CULL_FACE);
      glDisable(GL_BLEND);
    }
  }

  // Draw game objects
  void Draw(GameEntity const & obj)
  {
    m_texturedRect->Render(obj.m_texture->at(obj.m_textureIndex), QVector2D(obj.m_position.x(), obj.m_position.y()), QSize(obj.m_width, obj.m_height), m_screenSize, Settings::resolutionRate);
  }

  // Draw gun + shield
  void DrawGun(GameEntity const & obj, bool shield)
  {
    Draw(obj);
    if (shield)
      m_texturedRect->Render(m_shieldTexture, QVector2D(obj.m_position.x(), obj.m_position.y()), QSize(obj.m_width*1.625, obj.m_height*1.625), m_screenSize, Settings::resolutionRate);
  }

  // Draw explosions animation
  void DrawExplosion(Explosion const & obj)
  {
    m_texturedRect->Render(m_explosionTexture, QVector2D(obj.m_position.x(), obj.m_position.y()), QSize(obj.m_width, obj.m_height), m_screenSize, Settings::resolutionRate, false, obj.m_frame, obj.m_frameCount);
  }

  // Draw stars on background
  void DrawBackground(GameEntity const & star, bool isPause)
  {
    m_texturedRect->Render(m_starTexture, QVector2D(star.m_position.x(), star.m_position.y()), QSize(star.m_width, star.m_height), m_screenSize, Settings::resolutionRate, !isPause);
  }

  void DrawPanel(int const score, int const level, int const health, bool bonusShield, bool bonusWeapon)
  {
    float x = Settings::windowWidth/2 - (health + bonusShield + bonusWeapon) * 40 / 2 + 20;
    for (int i = 0; i < health; ++i)
      m_texturedRect->Render(m_heartTexture, QVector2D(x + i*40, 560), QSize(30, 30), m_screenSize, Settings::resolutionRate);
    if (bonusShield)
      m_texturedRect->Render(m_bonusTexture[1], QVector2D(x + health*40 + 2, 560), QSize(26, 30), m_screenSize, Settings::resolutionRate);
    if (bonusWeapon)
      m_texturedRect->Render(m_bonusTexture[2], QVector2D(x + health*40 + 2, 560), QSize(26, 30), m_screenSize, Settings::resolutionRate);

    Blending(false);

    DrawText("SCORE", 20, 60, 50, Qt::white);
    DrawText("LEVEL", 570, 60, 50, Qt::white);
    DrawText(QString::number(score), 170, 60, 50, Qt::green);
    DrawText(QString::number(level), 720, 60, 50, Qt::green);

    DrawLine(20, 70, 780, 70, 3, Qt::white);

    Blending(true);
  }

  void DrawMenu(int const menuItem)
  {
    m_texturedRect->Render(m_menuAlienTexture, QVector2D(270, 303 - menuItem*45), QSize(40, 40), m_screenSize, Settings::resolutionRate);
    m_texturedRect->Render(m_menuAlienTexture, QVector2D(530, 303 - menuItem*45), QSize(40, 40), m_screenSize, Settings::resolutionRate);

    Blending(false);

    DrawText("SPACE INVADERS", 40, 150, 100, Qt::white);
    DrawText("START", 340, 320, 50, Qt::white);
    DrawText("OPTIONS", 310, 365, 50, Qt::white);
    DrawText("EXIT", 355, 410, 50, Qt::white);

    Blending(true);
  }

  void DrawOptions()
  {
    m_texturedRect->Render(m_menuAlienTexture, QVector2D(260, 348 - Settings::optionItem*90), QSize(40, 40), m_screenSize, Settings::resolutionRate);
    m_texturedRect->Render(m_menuAlienTexture, QVector2D(540, 348 - Settings::optionItem*90), QSize(40, 40), m_screenSize, Settings::resolutionRate);
    if (Settings::gunSkinItem == 0)
      m_texturedRect->Render(m_questionTexture, QVector2D(400, 120), QSize(40, 40), m_screenSize, Settings::resolutionRate);
    else
      m_texturedRect->Render(m_gunTexture["good"][Settings::gunSkinItem-1], QVector2D(400, 120), QSize(40, 40), m_screenSize, Settings::resolutionRate);

    Blending(false);

    DrawText("SPACE INVADERS", 40, 150, 100, Qt::white);
    DrawText("DIFFICULTY", 275, 230, 50, Qt::white);
    DrawText("RESOLUTION", 270, 320, 50, Qt::white);
    DrawText("GUN SKIN", 297, 410, 50, Qt::white);
    DrawText("OK", 375, 545, 50, Qt::white);

    auto & res = Settings::resolution[Settings::resolutionItem];
    DrawText(QString::fromStdString(Settings::difficulty[Settings::difficultyItem]), 0, 275, 50, Qt::green, true);
    DrawText(QString::number(res.first) + "x" + QString::number(res.second), 0, 365, 50, Qt::green, true);
    DrawText(Settings::gunSkinItem == 0 ? "RANDOM" : "GUN " + QString::number(Settings::gunSkinItem), 0, 455, 50, Qt::green, true);

    Blending(true);
  }

  void DrawLevelLoad(int const level, int loadLevelDuration)
  {
    if (!(m_loadLevelPosition >= 340 && loadLevelDuration < Settings::loadLevelPause))
      m_loadLevelPosition += Settings::loadLevelStep;

    Blending(false);
    DrawText("LEVEL " + QString::number(level), 0, m_loadLevelPosition, 100, Qt::white, true);
    Blending(true);
  }

  void DrawEndMenu(int const score, int const menuItem)
  {
    m_texturedRect->Render(m_menuAlienTexture, QVector2D(270, 258 - menuItem*45), QSize(40, 40), m_screenSize, Settings::resolutionRate);
    m_texturedRect->Render(m_menuAlienTexture, QVector2D(530, 258 - menuItem*45), QSize(40, 40), m_screenSize, Settings::resolutionRate);

    Blending(false);

    DrawText("GAME OVER", 170, 150, 100, Qt::white);
    DrawText("HIGH SCORE", 210, 220, 50, Qt::white);
    DrawText("SCORE", 340, 270, 50, Qt::white);
    DrawText("MENU", 352, 365, 50, Qt::white);
    DrawText("EXIT", 355, 410, 50, Qt::white);
    DrawText(QString::number(Settings::highScore), 490, 220, 50, Qt::green);
    DrawText(QString::number(score), 490, 270, 50, Qt::green);

    Blending(true);
  }

  std::unordered_map<std::string, std::vector<QOpenGLTexture *>> m_gunTexture;
  std::vector<QOpenGLTexture *> m_alienTexture;
  std::unordered_map<std::string, std::vector<QOpenGLTexture *>> m_obstacleTexture;
  std::vector<QOpenGLTexture *> m_bulletTexture;
  std::vector<QOpenGLTexture *> m_bonusTexture;
  QOpenGLTexture * m_menuAlienTexture = nullptr;
  QOpenGLTexture * m_heartTexture = nullptr;
  QOpenGLTexture * m_starTexture = nullptr;
  QOpenGLTexture * m_questionTexture = nullptr;
  QOpenGLTexture * m_shieldTexture = nullptr;
  QOpenGLTexture * m_explosionTexture = nullptr;
  QSize m_screenSize;
  QPainter m_painter;
  float m_loadLevelPosition = 0;

private:
  friend class Singleton<Renderer>;

  // Constructor
  Renderer() = default;

  void DrawText(QString text, float x, float y, int size, QColor color, bool inCenter = false)
  {
    if (!m_painter.isActive())
      return;

    auto & rate = Settings::resolutionRate;
    QFont font = m_painter.font();
    font.setFamily("Arcade");
    font.setPointSize(size * rate);

    // Center text
    if (inCenter)
    {
      QFontMetrics fMetric(font);
      x = (m_screenSize.width() - fMetric.width(text)) / 2;
    }
    else
    {
      x *= rate;
    }

    m_painter.setFont(font);
    m_painter.setPen(color);
    m_painter.drawText(x, y * rate, text);
  }

  void DrawLine(float x1, float y1, float x2, float y2, int width, QColor color)
  {
    if (!m_painter.isActive())
      return;

    auto & rate = Settings::resolutionRate;
    m_painter.setPen(QPen(color, width * rate, Qt::SolidLine));
    m_painter.drawLine(x1*rate, y1*rate, x2*rate, y2*rate);
  }

  TexturedRect * m_texturedRect = nullptr;
};
