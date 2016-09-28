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
    double tmin = std::numeric_limits<double>::min(), tmax = std::numeric_limits<double>::max();
    float angle_deg = Atan360(m_origin, m_direction);
    float angle_rad = angle_deg * M_PI / 180;
    float endx = cos(angle_rad);  // dirx
    float endy = sin(angle_rad);  // diry
    Point2D pmax = Point2D(endx, endy);

    // Debug line
    //std:: cout<<m_direction<<"; Radians = "<<angle_rad<<"; Degrees = "<<angle_deg<<std::endl;

    for (int i = 0; i < 2; ++i)
    {
      if (pmax[i] != 0.0)
      {
        double t1 = (obj.boxMin()[i] - m_origin[i])/pmax[i];
        double t2 = (obj.boxMax()[i] - m_origin[i])/pmax[i];

        tmin = std::max(tmin, std::min(t1, t2));
        tmax = std::min(tmax, std::max(t1, t2));
      }
      else if (m_origin[i] <= obj.boxMin()[i] || m_origin[i] >= obj.boxMax()[i])
        return false;
    }

    return tmax > tmin && tmax > 0.0;
  }
private:
  // Extend Atan to 0-360 degrees
  float Atan360(const Point2D startPoint, const Point2D endPoint) const
  {
    // Get origin point to origin by subtracting end from start
    Point2D originPoint(endPoint.x() - startPoint.x(), endPoint.y() - startPoint.y());
    // Get bearing in radians
    float bearingRadians = atan2f(originPoint.y(), originPoint.x());
    // Convert to degrees
    float bearingDegrees = bearingRadians * 180.0 / M_PI;
    // Correct discontinuity
    bearingDegrees = bearingDegrees > 0.0 ? bearingDegrees : (360.0 + bearingDegrees);
    return bearingDegrees;
  }

  Point2D m_origin {0, 0};
  Point2D m_direction = {0, 0};
};

std::ostream & operator << (std::ostream & os, Ray2D const & obj)
{
  os << "Ray2D { Origin: " << obj.o() << ", Direction: " << obj.d() << " }";
  return os;
}