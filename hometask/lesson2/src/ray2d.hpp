#pragma once

#include <iostream>
#include <cmath>
#include <limits>
#include "point2d.hpp"
#include "box2d.hpp"

class Ray2D
{
public:
  // Constructors
  Ray2D() = default;

  Ray2D(float x1, float y1, float angle)
    : m_origin(x1, y1), m_angle(angle)
  {}

  Ray2D(Point2D p1, float angle)
    : m_origin(p1), m_angle(angle)
  {}

  // Copy constructor
  Ray2D(Ray2D const & obj)
    : m_origin(obj.m_origin), m_angle(obj.m_angle)
  {}

  // Getters
  Point2D & o() { return m_origin; }
  float & a() { return m_angle; }
  Point2D const & o() const { return m_origin; }
  float const & a() const { return m_angle; }

  // Assignment operator
  Ray2D & operator = (Ray2D const & obj)
  {
    if (this == & obj) return *this;
    m_origin = obj.m_origin;
    m_angle = obj.m_angle;
    return *this;
  }

  // Logical operators
  bool operator == (Ray2D const & obj) const
  {
    return m_origin == obj.m_origin && EqualWithEps(m_angle, obj.m_angle);
  }
  bool operator != (Ray2D const & obj) const
  {
    return !operator==(obj);
  }

  // Functionality
  bool IntersectBox(Box2D const & obj) const
  {
    double tmin = std::numeric_limits<double>::min(), tmax = std::numeric_limits<double>::max();
    float radian = m_angle * M_PI / 180;
    float endx = cos(radian) * LONG_MAX;  // dirx
    float endy = sin(radian) * LONG_MAX;  // diry
    Point2D pmax = Point2D(endx, endy);

    for (int i = 0; i < 2; ++i)
    {
      if (pmax[i] != 0.0)
      {
        double t1 = (obj.boxMin()[i] - m_origin[i]) / pmax[i];
        double t2 = (obj.boxMax()[i] - m_origin[i]) / pmax[i];

        tmin = std::max(tmin, std::min(t1, t2));
        tmax = std::min(tmax, std::max(t1, t2));
      }
      else if (m_origin[i] <= obj.boxMin()[i] || m_origin[i] >= obj.boxMax()[i])
        return false;
    }

    return tmax > tmin && tmax > 0.0;
  }
private:
  Point2D m_origin {0, 0};
  float m_angle = 0;
};

std::ostream & operator << (std::ostream & os, Ray2D const & obj)
{
  os << "Ray2D { " << obj.o() << ", Angle: " << obj.a() << " }";
  return os;
}