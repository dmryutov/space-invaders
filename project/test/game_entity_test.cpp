#include "gtest/gtest.h"
#include "../src/game_entity.hpp"

TEST(game_entity_test, test_construction)
{
  // Constructors
  GameEntity ge1;
  EXPECT_EQ(ge1.m_width, 1);
  EXPECT_EQ(ge1.m_height, 1);
  EXPECT_EQ(ge1.m_health, 1);
  EXPECT_EQ(ge1.m_position, Point2D(0, 0));
}

TEST(game_entity_test, test_move)
{
  GameEntity ge1;
  ge1.m_position = {50, 40};

  ge1.Move(GameEntity::MOVE_LEFT);
  EXPECT_EQ(ge1.m_position, Point2D(40, 40));

  ge1.Move(GameEntity::MOVE_RIGHT);
  EXPECT_EQ(ge1.m_position, Point2D(50, 40));

  ge1.Move(GameEntity::MOVE_DOWN);
  EXPECT_EQ(ge1.m_position, Point2D(50, 30));

  ge1.Move(GameEntity::MOVE_UP);
  EXPECT_EQ(ge1.m_position, Point2D(50, 40));
}