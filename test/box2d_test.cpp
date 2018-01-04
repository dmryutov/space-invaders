#include <sstream>
#include "gtest/gtest.h"
#include "../src/box2d.hpp"

TEST(box2d_test, test_construction)
{
  // Constructors
  Box2D b1;
  EXPECT_EQ(b1.boxMin(), Point2D(0, 0));
  EXPECT_EQ(b1.boxMax(), Point2D(1, 1));

  Box2D b2 {1.2, 2.4, 3.1, 5.8};
  EXPECT_EQ(b2.boxMin(), Point2D(1.2, 2.4));
  EXPECT_EQ(b2.boxMax(), Point2D(3.1, 5.8));

  Box2D b3 {Point2D(1.2, 2.4), Point2D(3.1, 5.8)};
  EXPECT_EQ(b3.boxMin(), Point2D(1.2, 2.4));
  EXPECT_EQ(b3.boxMax(), Point2D(3.1, 5.8));

  Box2D b4 {Point2D(1.2, 2.4), 1.9, 3.4};
  EXPECT_EQ(b4.boxMin(), Point2D(1.2, 2.4));
  EXPECT_EQ(b4.boxMax(), Point2D(3.1, 5.8));

  // Copy constructor
  Box2D b5 = b4;
  EXPECT_EQ(b5, b4);

  // Move constructor
  Box2D b6(Box2D(1.2, 2.4, 3.1, 5.8));
  EXPECT_EQ(b6, Box2D(1.2, 2.4, 3.1, 5.8));
}

TEST(box2d_test, test_construction_exception)
{
  Box2D b1 {1.2, 2.4, 1.2, 2.4};
  EXPECT_EQ(b1.boxMin(), Point2D(0, 0));
  EXPECT_EQ(b1.boxMax(), Point2D(1, 1));
}

TEST(box2d_test, test_assignment)
{
  Box2D b1;
  b1 = {1.2, 2.4, 3.1, 5.8};
  EXPECT_EQ(b1, Box2D(1.2, 2.4, 3.1, 5.8));
}

TEST(box2d_test, test_move)
{
  Box2D b1 {1.2, 2.4, 3.1, 5.8};
  Box2D b2 = std::move(b1);
  EXPECT_EQ(b2, Box2D(1.2, 2.4, 3.1, 5.8));
}

TEST(box2d_test, test_equality)
{
  Box2D b1 {1.2, 2.4, 3.1, 5.8};
  Box2D b2 {1.2, 2.4, 3.1, 5.8};
  Box2D b3 {1.2, 2.4, 4.2, 4.9};
  EXPECT_EQ(b1, b2);
  EXPECT_NE(b1, b3);
}

TEST(box2d_test, test_intersection)
{
  Box2D b1(1, 1, 4, 2);
  Box2D b2(2, 0, 3, 3);
  Box2D b3(8, 1, 10, 3);

  EXPECT_TRUE(b1.IntersectBox(b2));
  EXPECT_FALSE(b1.IntersectBox(b3));
}

TEST(box2d_test, test_middle)
{
  Box2D b1 {1.2, 2.4, 3.1, 5.8};
  EXPECT_EQ(b1.xMiddle(), 2.15);
  EXPECT_EQ(b1.yMiddle(), 4.1);
}

TEST(box2d_test, test_output)
{
  std::stringstream ss;
  ss << Box2D(1.2, 2.4, 3.1, 5.8);
  EXPECT_EQ(ss.str(), "Box2D { Point2D {1.2, 2.4}, Point2D {3.1, 5.8} }");
}