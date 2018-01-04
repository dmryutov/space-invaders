#include "gtest/gtest.h"
#include "../src/alien.hpp"

TEST(alien_test, test_construction)
{
  // Constructors
  Alien a1 {50, 40, 10, 1};
  EXPECT_EQ(a1.m_width, 40);
  EXPECT_EQ(a1.m_height, 40);
  EXPECT_EQ(a1.m_health, 1);
  EXPECT_EQ(a1.m_position, Point2D(50, 40));
}

TEST(alien_test, test_shoot)
{
  Alien a1 {50, 40, 10, 1};
  std::list<Bullet> b1;

  a1.Shoot(b1);
  ASSERT_EQ(b1.size(), 1);
  EXPECT_EQ(b1.back().m_fromPlayer, false);
  EXPECT_EQ(b1.back().m_position, Point2D(68, 80));
}

TEST(alien_test, test_output)
{
  std::stringstream ss;
  ss << Alien(50, 40, 10, 1);
  EXPECT_EQ(ss.str(), "Alien: {Position: Point2D {50, 40}, Speed: 10, Health: 1}");
}