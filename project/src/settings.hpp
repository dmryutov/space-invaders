#pragma once

#include <QMainWindow>
#include <QDir>
#include "PugiXML/pugixml.cpp"
#include "file_settings.hpp"
#include "log.hpp"
#include "patterns.hpp"

namespace Settings
{
std::string programPath;
Factory factory;

// Load level animation
float const loadLevelStep = 10;
int const loadLevelPause = 1000;
int const loadLevelEndPause = 300;

// Gun
float const gunWidth = 50;
float const gunHeight = 50;
int gunHealth;
float const gunSpeed = 10;
int const gunShootDelay = 300;
int const gunShootBonusDelay = 50;
int const gunTextureCount = 10;

// Alien
float const alienWidth = 50;
float const alienHeight = 50;
int alienRowCount = 3;
int alienColCount = 8;
int alienHealth = 1;
int alienHealthInc;
float alienSpeed;
float alienSpeedInc;
float alienShootPossibility;
float alienShootPossibilityInc;
float alienRayWidth;
int const alienTextureCount = 15;

// Bullet
float const bulletWidth = 3;
float const bulletHeight = 15;
float const bulletSpeed = 7;
int const bulletTextureCount = 2;

// Obstacle
float const obstacleWidth = 100;
float const obstacleHeight = 50;
int obstacleHealth;
int obstacleCount = 3;
int const obstacleTextureCount = 3;

// Bonus
float const bonusWidth = 39;
float const bonusHeight = 46.5;
float bonusSpeed;
int const bonusDelay = 800;
int const bonusShieldDuration = 300;
int const bonusWeaponDuration = 300;
int const bonusTextureCount = 3;

// Star
int const starCount = 60;

// Explosion
int const explosionSpeed = 20;
int const explosionFrames = 15;

// Options
std::string const settingsFile = "/data/settings.xml";
int optionItem = 0;
int difficultyItem = 1;
int gunSkinItem = 0;
int resolutionItem = 1;
int const windowWidth = 800;
int const windowHeight = 600;
float resolutionRate = 1;
std::vector<std::string> const difficulty {"EASY", "MEDIUM", "HARD", "NIGHTMARE"};
std::vector<std::pair<int, int>> const resolution {
  {640, 480},
  {800, 600},
  {1280, 960}
};
MainWindow * pMainWindow = nullptr;
int highScore = 0;

void SetDifficulty(int index)
{
  switch (index)
  {
    case 0:
      gunHealth = 3;
      alienHealthInc = 15;
      alienSpeed = 2;
      alienSpeedInc = 0.2;
      alienShootPossibility = 1.3;
      alienShootPossibilityInc = 0.04;
      alienRayWidth = 40;
      obstacleHealth = 10;
      bonusSpeed = 4;
      break;
    case 1:
      gunHealth = 3;
      alienHealthInc = 12;
      alienSpeed = 4;
      alienSpeedInc = 0.3;
      alienShootPossibility = 1.6;
      alienShootPossibilityInc = 0.06;
      alienRayWidth = 50;
      obstacleHealth = 8;
      bonusSpeed = 6;
      break;
    case 2:
      gunHealth = 2;
      alienHealthInc = 9;
      alienSpeed = 6;
      alienSpeedInc = 0.4;
      alienShootPossibility = 2;
      alienShootPossibilityInc = 0.08;
      alienRayWidth = 60;
      obstacleHealth = 6;
      bonusSpeed = 8;
      break;
    case 3:
      gunHealth = 1;
      alienHealthInc = 5;
      alienSpeed = 8;
      alienSpeedInc = 0.5;
      alienShootPossibility = 2.3;
      alienShootPossibilityInc = 0.1;
      alienRayWidth = 70;
      obstacleHealth = 2;
      bonusSpeed = 10;
      break;
  }
}

void ChangeResolution()
{
  auto & res = resolution[resolutionItem];
  pMainWindow->setFixedSize(res.first, res.second);
  resolutionRate = (float)res.first / windowWidth;
}

// Load settings from file
void Load(MainWindow * mw)
{
  // Load settings
  pugi::xml_document doc;
  doc.load_file((Settings::programPath + settingsFile).c_str());
  auto game = doc.child("game");
  if (game.attribute("difficulty"))
    difficultyItem = game.attribute("difficulty").as_int();
  if (game.attribute("resolution"))
    resolutionItem = game.attribute("resolution").as_int();
  if (game.attribute("highscore"))
    highScore = game.attribute("highscore").as_int();
  auto gun = doc.child("gun");
  if (gun.attribute("skin"))
    gunSkinItem = gun.attribute("skin").as_int();

  // Set window resolution
  pMainWindow = mw;
  ChangeResolution();

  SetDifficulty(difficultyItem);
}

// Save settings to file
void Save()
{
  // Create data dir if not exists
  QDir dir("data");
  if (!dir.exists())
    dir.mkpath(".");

  // Save settings
  pugi::xml_document tree;
  auto game = tree.append_child("game");
  game.append_attribute("difficulty") = difficultyItem;
  game.append_attribute("resolution") = resolutionItem;
  game.append_attribute("highscore") = highScore;
  auto gun = tree.append_child("gun");
  gun.append_attribute("skin") = gunSkinItem;
  tree.save_file((Settings::programPath + settingsFile).c_str());

  SetDifficulty(difficultyItem);
}

}
