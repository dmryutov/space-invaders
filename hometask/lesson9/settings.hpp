#pragma once

#include "log.hpp"
#include "patterns.hpp"

namespace Settings
{
Factory factory;

int const windowWidth = 640;
int const windowHeight = 480;
int const windowTimeout = 100;

// Object dimensions
float const gunWidth = 40;
float const gunHeight = 40;
float const alienWidth = 40;
float const alienHeight = 40;
float const bulletWidth = 4;
float const bulletHeight = 4;
float const obstacleWidth = 80;
float const obstacleHeight = 40;

//Object count
int alienRow = 9;
int alienCol = 3;
int obstacleCount = 3;

int gunHealth = 3;
float const gunSpeed = 10;

int alienHealthInc = 15;
float alienSpeed = 4.5;
float alienSpeedInc = 0.5;
float alienShootPossibility = 4.5;  // 1.3
float alienShootPossibilityInc = 0.2;
int obstacleHealth = 10;

void GameDifficulty(int index) {
  switch (index) {
    case 0:
      gunHealth = 3;
      alienHealthInc = 15;
      alienSpeed = 4.5;
      alienSpeedInc = 0.5;
      alienShootPossibility = 4;  // 1.3
      alienShootPossibilityInc = 0.2;
      obstacleHealth = 10;
      break;
    case 1:
      gunHealth = 3;
      alienHealthInc = 12;
      alienSpeed = 6;
      alienSpeedInc = 0.7;
      alienShootPossibility = 4.5;  // 1.3
      alienShootPossibilityInc = 0.3;
      obstacleHealth = 8;
      break;
    case 2:
      gunHealth = 2;
      alienHealthInc = 9;
      alienSpeed = 8;
      alienSpeedInc = 1.1;
      alienShootPossibility = 5.5;  // 1.3
      alienShootPossibilityInc = 0.4;
      obstacleHealth = 6;
      break;
    case 3:
      gunHealth = 1;
      alienHealthInc = 5;
      alienSpeed = 12;
      alienSpeedInc = 1.7;
      alienShootPossibility = 8;  // 1.3
      alienShootPossibilityInc = 0.6;
      obstacleHealth = 2;
      break;
  }
}

}
