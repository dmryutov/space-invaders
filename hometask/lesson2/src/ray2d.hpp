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

  Ray2D(float x1, float y1, float x2, float y2)
    : m_origin(x1, y1), m_direction(x2, y2)
  {}

  Ray2D(Point2D p1, Point2D p2)
    : m_origin(p1), m_direction(p2)
  {}

  // Copy constructor
  Ray2D(Ray2D const & obj)
    : m_origin(obj.m_origin), m_direction(obj.m_direction)
  {}

  // Move constructor
  Ray2D(Ray2D && obj)
    : m_origin(std::move(obj.m_origin)), m_direction(std::move(obj.m_direction))
  {}

  // Getters
  Point2D & o() { return m_origin; }
  Point2D & d() { return m_direction; }
  Point2D const & o() const { return m_origin; }
  Point2D const & d() const { return m_direction; }

  // Assignment operator
  Ray2D & operator = (Ray2D const & obj)
  {
    if (this == &obj) return *this;
    m_origin = obj.m_origin;
    m_direction = obj.m_direction;
    return *this;
  }

  // Move operator
  Ray2D & operator = (Ray2D && obj)
  {
    std::swap(m_origin, obj.m_origin);
    std::swap(m_direction, obj.m_direction);
    return *this;
  }

  // Logical operators
  bool operator == (Ray2D const & obj) const
  {
    return m_origin == obj.m_origin && m_direction == obj.m_direction;
  }
  bool operator != (Ray2D const & obj) const
  {
    return !operator==(obj);
  }

  // Functionality
  bool IntersectBox(Box2D const & obj) const
  {
    // Normalise direction vector
    float xdir = m_direction.x() - m_origin.x();  // x direction
    float ydir = m_direction.y() - m_origin.y();  // y direction

    // Length of direction vector
    float length = sqrt(xdir * xdir + ydir * ydir);
    //std::cout << "Length = " << length << std::endl;
    // Unit vector
    Point2D unit_vec(xdir /= length, ydir /= length);
    //std::cout<<"Unit = "<<unit_vec<<std::endl;
    Point2D EndPoint = m_origin + unit_vec * std::numeric_limits<float>::max();
    //std::cout<<"EndPoint = "<<EndPoint<<std::endl;
    double tmin = std::numeric_limits<double>::min(), tmax = std::numeric_limits<double>::max();

    for (int i = 0; i < 2; ++i)
    {
      if (EndPoint[i] != 0.0)
      {
        double t1 = (obj.boxMin()[i] - m_origin[i])/EndPoint[i];
        double t2 = (obj.boxMax()[i] - m_origin[i])/EndPoint[i];

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
  Point2D m_direction {0, 0};
};

std::ostream & operator << (std::ostream & os, Ray2D const & obj)
{
  os << "Ray2D { Origin: " << obj.o() << ", Direction: " << obj.d() << " }";
  return os;
}