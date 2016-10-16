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
  try
  {
    Obstacle o1 {1, 0};
  }
  catch (std::exception const & ex)
  {
    EXPECT_EQ(ex.what(), "Amount of obstacles should be greater than 0!");
  }
}