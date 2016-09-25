#pragma once

#include <iostream>
#include "point2d.hpp"
#include "box2d.hpp"

class Ray2D: public Point2D
{
public:
  // Constructors
  Ray2D() = delete;
  Ray2D(float x1, float y1, float xdir, float ydir)
    : m_origin({x1, y1}), m_direction(xdir, ydir)
  {}
  Ray2D(Point2D p1, Point2D p2)
    : m_origin(p1), m_direction(p2)
  {}

  // Copy constructor
  Ray2D(Ray2D const &obj)
    : m_origin(obj.m_origin), m_direction(obj.m_direction)
  {}

  // Getters
  Point2D &o() { return m_origin; }
  Point2D &d() { return m_direction; }
  Point2D const &o() const { return m_origin; }
  Point2D const &d() const { return m_direction; }

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
      float tmin = (obj.p1()[0] - m_origin[0]) / m_direction[0];
      float tmax = (obj.p2()[0] - m_origin[0]) / m_direction[0];

      if (tmin > tmax) std::swap(tmin, tmax);

      float tymin = (obj.p1()[1] - m_origin[1]) / m_direction[1];
      float tymax = (obj.p2()[1] - m_origin[1]) / m_direction[1];

      if (tymin > tymax) std::swap(tymin, tymax);

      if ((tmin > tymax) || (tymin > tmax))
          return false;

      if (tymin > tmin)
          tmin = tymin;

      if (tymax < tmax)
          tmax = tymax;

      return true;
  }

private:
  Point2D m_origin {0, 0};
  Point2D m_direction = {0, 0};
};

std::ostream &operator << (std::ostream &os, Ray2D const &obj)
{
  os << "Ray2D { " << obj.o() << ", " << obj.d() << " }";
  return os;
}
