#pragma once

#include <QtGui/QMouseEvent>
#include <unordered_map>
#include "settings.hpp"

#define ACTIONS ActionManager::Instance().m_actions

class ActionManager: public Singleton<ActionManager>
{
public:
  void PressKey(int key)
  {
    m_actions[GetActionByKey(key)] = true;
  }

  void ReleaseKey(int key)
  {
    m_actions[GetActionByKey(key)] = false;
  }

  // Release key if action is single
  void SingleAction(int key)
  {
    m_actions[key] = false;
  }

  enum Keys {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SHOOT, KEY_ENTER, KEY_PAUSE, KEY_QUIT};
  std::unordered_map<char, bool> m_actions;
private:
  friend class Singleton<ActionManager>;

  // Constructor
  ActionManager()
  {
    m_keys[Qt::Key_Up] = KEY_UP;  // Up arrow
    m_keys[Qt::Key_Left] = KEY_LEFT;  // Left arrow
    m_keys[Qt::Key_Down] = KEY_DOWN;  // Down arrow
    m_keys[Qt::Key_Right] = KEY_RIGHT;  // Right arrow

    m_keys[Qt::Key_Space] = KEY_SHOOT;
    m_keys[Qt::Key_Enter] = KEY_ENTER;
    m_keys[Qt::Key_Return] = KEY_ENTER;  // Enter
    m_keys[Qt::Key_P] = KEY_PAUSE;
    m_keys[Qt::Key_Escape] = KEY_QUIT;
    m_keys[Qt::Key_Q] = KEY_QUIT;
  }

  char GetActionByKey(int key)
  {
    auto it = m_keys.find(key);
    return it != m_keys.end() ? it->second : -1;
  }

  std::unordered_map<int, char> m_keys;
};
