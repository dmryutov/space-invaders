#include <sstream>
#include "gtest/gtest.h"
#include "../src/ray2d.hpp"
#include "../src/box2d.hpp"

TEST(ray2d_test, test_construction)
{
  // Constructors
  Ray2D r1;
  EXPECT_EQ(r1.o(), Point2D(0, 0));
  EXPECT_EQ(r1.d(), 0);

  Ray2D r2 {1.2, 2.4, 45};
  EXPECT_EQ(r2.o(), Point2D(1.2, 2.4));
  EXPECT_EQ(r2.d(), 45);

  Ray2D r3 {Point2D(1.2, 2.4), 45};
  EXPECT_EQ(r3.o(), Point2D(1.2, 2.4));
  EXPECT_EQ(r3.d(), 45);

  // Copy constructor
  Ray2D r4 = r3;
  EXPECT_EQ(r4, r3);
}

TEST(ray2d_test, test_assignment)
{
  Ray2D r1;
  r1 = {1.2, 2.4, 45};
  EXPECT_EQ(r1, Ray2D(1.2, 2.4, 45));
}

TEST(ray2d_test, test_equality)
{
  Ray2D r1 {1.2, 2.4, 45};
  Ray2D r2 {1.2, 2.4, 45};
  Ray2D r3 {3.6, 4.1, 87};
  EXPECT_EQ(r1, r2);
  EXPECT_NE(r1, r3);
}

TEST(ray2d_test, test_intersection)
{
  Ray2D r1(6, 1, 80);
  Box2D b1(6, 2, 7, 5);
  Box2D b2(1, 1, 4, 2);

  EXPECT_TRUE(r1.IntersectBox(b1));
  EXPECT_FALSE(r1.IntersectBox(b2));
}

TEST(ray2d_test, test_output)
{
  std::stringstream ss;
  ss << Ray2D(1.2, 2.4, 45);
  EXPECT_EQ(ss.str(), "Ray2D { Point2D {1.2, 2.4}, 45 }");
}