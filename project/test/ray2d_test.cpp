#include <sstream>
#include "gtest/gtest.h"
#include "../src/ray2d.hpp"
#include "../src/box2d.hpp"

TEST(ray2d_test, test_construction)
{
  // Constructors
  Ray2D r1;
  EXPECT_EQ(r1.o(), Point2D(0, 0));
  EXPECT_EQ(r1.d(), Point2D(1, 1));

  Ray2D r2 {1.2, 2.4, 3.1, 5.8};
  EXPECT_EQ(r2.o(), Point2D(1.2, 2.4));
  EXPECT_EQ(r2.d(), Point2D(3.1, 5.8));

  Ray2D r3 {Point2D(1.2, 2.4), Point2D(3.1, 5.8)};
  EXPECT_EQ(r3.o(), Point2D(1.2, 2.4));
  EXPECT_EQ(r3.d(), Point2D(3.1, 5.8));

  // Copy constructor
  Ray2D r4 = r3;
  EXPECT_EQ(r4, r3);

  // Move constructor
  Ray2D r5(Ray2D(1.2, 2.4, 3.1, 5.8));
  EXPECT_EQ(r5, Ray2D(1.2, 2.4, 3.1, 5.8));
}

TEST(ray2d_test, test_construction_exception)
{
  Ray2D r1 {1.2, 2.4, 1.2, 2.4};
  EXPECT_EQ(r1.o(), Point2D(0, 0));
  EXPECT_EQ(r1.d(), Point2D(1, 1));
}

TEST(ray2d_test, test_assignment)
{
  Ray2D r1;
  r1 = {1.2, 2.4, 3.1, 5.8};
  EXPECT_EQ(r1, Ray2D(1.2, 2.4, 3.1, 5.8));
}

TEST(ray2d_test, test_move)
{
  Ray2D r1 {1.2, 2.4, 3.1, 5.8};
  Ray2D r2 = std::move(r1);
  EXPECT_EQ(r2, Ray2D(1.2, 2.4, 3.1, 5.8));
}

TEST(ray2d_test, test_equality)
{
  Ray2D r1 {1.2, 2.4, 3.1, 5.8};
  Ray2D r2 {1.2, 2.4, 3.1, 5.8};
  Ray2D r3 {3.6, 4.1, 6.5, 8.2};
  EXPECT_EQ(r1, r2);
  EXPECT_NE(r1, r3);
}

TEST(ray2d_test, test_box_intersection)
{
  Ray2D r1(6, 1, 8, 4);
  Box2D b1(6, 2, 7, 5);
  Box2D b2(1, 1, 4, 2);

  EXPECT_TRUE(r1.IntersectBox(b1));
  EXPECT_FALSE(r1.IntersectBox(b2));
}

TEST(ray2d_test, test_sector_intersection)
{
  Ray2D r1(3, 1, 3, 4);
  Box2D b1(1, 5, 2, 6);
  Box2D b2(3, 6, 4, 7);
  Box2D b3(5, 5, 6, 6);

  EXPECT_TRUE(r1.IntersectBox(b1, 1));
  EXPECT_TRUE(r1.IntersectBox(b2, 1));
  EXPECT_FALSE(r1.IntersectBox(b3, 1));
}

TEST(ray2d_test, test_output)
{
  std::stringstream ss;
  ss << Ray2D(1.2, 2.4, 3.1, 5.8);
  EXPECT_EQ(ss.str(), "Ray2D { Origin: Point2D {1.2, 2.4}, Direction: Point2D {3.1, 5.8} }");
}