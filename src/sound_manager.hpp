#pragma once

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <vector>
#include "settings.hpp"

class SoundManager: public Singleton<SoundManager>
{
public:
  void Play(int sound, bool loop = false)
  {
    if (m_sounds[sound]->state() == QMediaPlayer::PlayingState && !loop)
      m_sounds[sound]->setPosition(0);
    else if (m_sounds[sound]->state() == QMediaPlayer::StoppedState)
      m_sounds[sound]->play();
  }

  void Stop(int sound)
  {
    m_sounds[sound]->stop();
  }

  enum Sounds {MENU, SHOOT, BONUS, EXPLOSION, WIN, FAIL};
private:
  friend class Singleton<SoundManager>;

  // Constructor
  SoundManager()
  {
    m_playlist = new QMediaPlaylist;
    m_playlist->addMedia(QUrl("qrc:/data/sounds/space.mp3"));
    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);

    m_sounds.emplace_back(new QMediaPlayer());
    m_sounds[MENU]->setPlaylist(m_playlist);
    m_sounds.emplace_back(new QMediaPlayer());
    m_sounds[SHOOT]->setMedia(QUrl("qrc:/data/sounds/shoot.wav"));
    m_sounds.emplace_back(new QMediaPlayer());
    m_sounds[BONUS]->setMedia(QUrl("qrc:/data/sounds/bonus.wav"));
    m_sounds.emplace_back(new QMediaPlayer());
    m_sounds[EXPLOSION]->setMedia(QUrl("qrc:/data/sounds/explosion.wav"));
    m_sounds.emplace_back(new QMediaPlayer());
    m_sounds[WIN]->setMedia(QUrl("qrc:/data/sounds/win.wav"));
    m_sounds.emplace_back(new QMediaPlayer());
    m_sounds[FAIL]->setMedia(QUrl("qrc:/data/sounds/fail.wav"));
  }

  // Destructor
  ~SoundManager()
  {
    for (size_t i = 0; i < m_sounds.size(); ++i)
      delete m_sounds[i];
    m_sounds.clear();
  }

  std::vector<QMediaPlayer *> m_sounds;
  QMediaPlaylist * m_playlist;
};
