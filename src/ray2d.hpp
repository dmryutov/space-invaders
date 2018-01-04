#pragma once

#include <ostream>
#include <cmath>
#include <limits>
#include "point2d.hpp"
#include "box2d.hpp"
#include "log.hpp"

class Ray2D
{
public:
  // Constructors
  Ray2D() = default;

  Ray2D(float x1, float y1, float x2, float y2)
    : m_origin(x1, y1), m_direction(x2, y2)
  {
    CheckInit();
  }

  Ray2D(Point2D p1, Point2D p2)
    : m_origin(p1), m_direction(p2)
  {
    CheckInit();
  }

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

  // Check ray and box intersection
  bool IntersectBox(Box2D const & obj) const
  {
    Point2D unitVec = NormalizeVector(m_direction, m_origin);
    Point2D endPoint = m_origin + unitVec * std::numeric_limits<float>::max();
    double tMin = std::numeric_limits<double>::min(), tMax = std::numeric_limits<double>::max();

    for (int i = 0; i < 2; ++i)
    {
      if (endPoint[i] != 0.0)
      {
        double t1 = (obj.boxMin()[i] - m_origin[i]) / endPoint[i];
        double t2 = (obj.boxMax()[i] - m_origin[i]) / endPoint[i];

        tMin = std::max(tMin, std::min(t1, t2));
        tMax = std::min(tMax, std::max(t1, t2));
      }
      else if (m_origin[i] <= obj.boxMin()[i] || m_origin[i] >= obj.boxMax()[i])
        return false;
    }

    return tMax > tMin && tMax > 0.0;
  }

  // Check sector and box intersection
  bool IntersectSector(Box2D const & obj, float width)
  {
    float step = 0.2;
    bool res = false;
    float limit = m_direction.x() + width;
    m_direction.x() -= width;

    while (!res && m_direction.x() <= limit)
    {
      res = IntersectBox(obj);
      m_direction.x() += step;
    }
    
    // Return ray initial destination
    m_direction.x() = limit - width;
    return res;
  }

  // Normalize vector
  Point2D NormalizeVector(Point2D const m_dir, Point2D const m_orig) const
  {
    // Normalise direction vector
    float xDir = m_dir.x() - m_orig.x();  // x direction
    float yDir = m_dir.y() - m_orig.y();  // y direction
    // Length of direction vector
    float length = sqrt(xDir * xDir + yDir * yDir);

    return Point2D(xDir / length, yDir / length);
  }
private:
  // Check origin and direction equality
  void CheckInit()
  {
    try
    {
      if (m_origin == m_direction)
        throw std::invalid_argument("Origin and Direction shoud be different!");
    }
    catch (std::exception const & ex)
    {
      LOG(LOG_ERROR) << ex.what();
      m_origin = {0, 0};
      m_direction = {1, 1};
    }
  }

  Point2D m_origin {0, 0};
  Point2D m_direction {1, 1};
};

inline std::ostream & operator << (std::ostream & os, Ray2D const & obj)
{
  os << "Ray2D { Origin: " << obj.o() << ", Direction: " << obj.d() << " }";
  return os;
}
