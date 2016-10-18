#include "gtest/gtest.h"
#include "../src/alien_group.hpp"

TEST(alien_group_test, test_construction)
{
  // Constructors
  AlienGroup ag1;
  EXPECT_EQ(ag1.m_height, 1);
  EXPECT_EQ(ag1.m_height, 1);
  EXPECT_EQ(ag1.m_aliens.size(), 0);
  EXPECT_EQ(ag1.m_shootPossibility, 1);
  EXPECT_EQ(ag1.m_position, Point2D(0, 0));
}

TEST(alien_group_test, test_create)
{
  AlienGroup ag1;
  ag1.Create(1);

  float alienWidth = 600;  // 1.5 * 40 * 10
  float alienHeight = 180;  // 1.5 * 40 * 3

  EXPECT_EQ(ag1.m_shootPossibility, 1.2);
  EXPECT_EQ(ag1.m_width, alienWidth - 20);
  EXPECT_EQ(ag1.m_height, alienHeight - 20);
  EXPECT_EQ(ag1.m_aliens.size(), 30);
  EXPECT_EQ(ag1.m_position, Point2D(350 - alienWidth / 2, 70));  // (640 - alienWidth) / 2 + 30
}

TEST(alien_group_test, test_reset)
{
  AlienGroup ag1;
  ag1.Reset();

  EXPECT_EQ(ag1.m_shootPossibility, 1.3);
}

TEST(alien_group_test, test_move)
{
  AlienGroup ag1;
  ag1.Create(1);
  ag1.Move();

  float alienWidth = 600;  // 1.5 * 40 * 10
  
  EXPECT_EQ(ag1.m_position, Point2D(350 - alienWidth / 2 - 10, 70));
}