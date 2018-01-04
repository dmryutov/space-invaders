#include "gtest/gtest.h"
#include "../src/gun.hpp"

TEST(gun_test, test_construction)
{
  // Constructors
  Gun g1;
  EXPECT_EQ(g1.m_width, 1);
  EXPECT_EQ(g1.m_height, 1);
  EXPECT_EQ(g1.m_health, 1);
  EXPECT_EQ(g1.m_position, Point2D(0, 0));
}

TEST(gun_test, test_create)
{
  Gun g1;
  g1.Create();

  EXPECT_EQ(g1.m_width, 40);
  EXPECT_EQ(g1.m_height, 40);
  EXPECT_EQ(g1.m_position, Point2D(300, 440));
}


TEST(gun_test, test_reset)
{
  Gun g1;
  g1.Reset();

  EXPECT_EQ(g1.m_health, 3);
}

TEST(gun_test, test_shoot)
{
  Gun g1;
  g1.Create();
  std::list<Bullet> b1;

  g1.Shoot(b1);
  ASSERT_EQ(b1.size(), 1);
  EXPECT_EQ(b1.back().m_fromPlayer, true);
  EXPECT_EQ(b1.back().m_position, Point2D(318, 436));
}

TEST(gun_test, test_output)
{
  Gun g1;
  g1.Create();
  std::stringstream ss;
  ss << g1;
  EXPECT_EQ(ss.str(), "Gun: {Position: Point2D {300, 440}, Health: 1, Speed: 10}");
}