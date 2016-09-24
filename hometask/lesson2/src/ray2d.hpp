#pragma once

#include <iostream>
#include "point2d.hpp"

class Ray2D: public Point2D
{
public:
  // Constructors
  Ray2D() = default;
  Ray2D(float x1, float y1, float d)
    : m_origin({x1, y1}), m_direction(d)
  {}
  Ray2D(Point2D p1, float d)
    : m_origin(p1), m_direction(d)
  {}

  // Copy constructor
  Ray2D(Ray2D const &obj)
    : m_origin(obj.m_origin), m_direction(obj.m_direction)
  {}

  // Getters
  Point2D &o() { return m_origin; }
  float &d() { return m_direction; }
  Point2D const &o() const { return m_origin; }
  float const &d() const { return m_direction; }

  // Logical operators
  bool operator == (Ray2D const &obj) const
  {
    return m_origin == obj.m_origin && m_direction == obj.m_direction;
  }
  bool operator != (Ray2D const &obj) const
  {
    return !operator==(obj);
  }

  // Functionality
  bool IntersectBox(Box2D const &obj) const
  {
    return false;
  }
private:
  Point2D m_origin {0, 0};
  float m_direction = 0;
};

std::ostream &operator << (std::ostream &os, Ray2D const &obj)
{
  os << "Ray2D { " << obj.o() << ", " << obj.d() << " }";
  return os;
}