#include "gtest/gtest.h"
#include "../src/bullet.hpp"

TEST(bullet_test, test_construction)
{
  // Constructors
  Bullet b1 {50, 40, true};
  EXPECT_EQ(b1.m_health, 1);
  EXPECT_EQ(b1.m_width, 4);
  EXPECT_EQ(b1.m_height, 4);
  EXPECT_EQ(b1.m_fromPlayer, true);
  EXPECT_EQ(b1.m_position, Point2D(48, 36));

  Bullet b2 {50, 40, false};
  EXPECT_EQ(b2.m_health, 1);
  EXPECT_EQ(b2.m_width, 4);
  EXPECT_EQ(b2.m_height, 4);
  EXPECT_EQ(b2.m_fromPlayer, false);
  EXPECT_EQ(b2.m_position, Point2D(48, 40));
}

TEST(bullet_test, test_move)
{
  Bullet b1 {50, 40, true};
  b1.Move();
  EXPECT_EQ(b1.m_position, Point2D(48, 26));

  Bullet b2 {50, 40, false};
  b2.Move();
  EXPECT_EQ(b2.m_position, Point2D(48, 50));
}

TEST(bullet_test, test_output)
{
  std::stringstream ss;
  ss << Bullet(50, 40, true);
  EXPECT_EQ(ss.str(), "Bullet: {Position: Point2D {48, 36}, Speed: 10, FromPlayer: 1}");
}