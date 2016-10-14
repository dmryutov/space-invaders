#pragma once

#include "settings.hpp"
#include "game_entity.hpp"

class Renderer {
public:
  // Constructor
  Renderer() = default;

  // Functionality
  void Draw(GameEntity const & obj)
  {
    // Draw game objects
  }

  void DrawBackground()
  {

  }

  void DrawPanel(int const score, int const level, int const health)
  {
    // Draw score/level/health information panel
  }

  void DrawLevelLoad(int const level)
  {

  }

  void DrawMenu(int const menuItem)
  {

  }

  void DrawEndMenu(int const score, int const menuItem)
  {
    // Draw game over menu
  }
};