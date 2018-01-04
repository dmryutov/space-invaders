#include "gtest/gtest.h"
#include "../src/obstacle.hpp"

TEST(obstacle_test, test_construction)
{
  // Constructors
  Obstacle o1 {1, 3};
  EXPECT_EQ(o1.m_health, 10);
  EXPECT_EQ(o1.m_width, 80);
  EXPECT_EQ(o1.m_height, 40);

  int gap = (640 - 240) / 4;
  EXPECT_EQ(o1.m_position, Point2D(2 * gap + 80, 380));
}

TEST(obstacle_test, test_construction_exception)
{
  EXPECT_THROW(Obstacle(1, 0), std::exception);
}

TEST(obstacle_test, test_output)
{
  std::stringstream ss;
  ss << Obstacle(1, 3);
  EXPECT_EQ(ss.str(), "Obstacle: {Position: Point2D {280, 380}, Health: 10}");
}