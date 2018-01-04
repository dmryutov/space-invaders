#pragma once

#include <ostream>
#include "point2d.hpp"
#include "log.hpp"

class Box2D
{
public:
  // Constructors
  Box2D() = default;

  Box2D(float x1, float y1, float x2, float y2)
    : m_min(x1, y1), m_max(x2, y2)
  {
    PointSwap();
  }

  Box2D(Point2D p1, Point2D p2)
    : m_min(p1), m_max(p2)
  {
    PointSwap();
  }

  Box2D(Point2D p1, float w, float h)
    : m_min(p1.x() - w/2, p1.y() - h/2), m_max(p1.x() + w/2, p1.y() + h/2)
  {
    PointSwap();
  }

  // Copy constructor
  Box2D(Box2D const & obj)
    : m_min(obj.m_min), m_max(obj.m_max)
  {}

  // Move constructor
  Box2D(Box2D && obj)
    : m_min(std::move(obj.m_min)), m_max(std::move(obj.m_max))
  {}

  // Getters
  Point2D & boxMin() { return m_min; }
  Point2D & boxMax() { return m_max; }
  Point2D const & boxMin() const { return m_min; }
  Point2D const & boxMax() const { return m_max; }

  // Assignment operator
  Box2D & operator = (Box2D const & obj)
  {
    if (this == &obj) return *this;
    m_min = obj.m_min;
    m_max = obj.m_max;
    return *this;
  }

  // Move operator
  Box2D & operator = (Box2D && obj)
  {
    std::swap(m_min, obj.m_min);
    std::swap(m_max, obj.m_max);
    return *this;
  }

  // Logical operators
  bool operator == (Box2D const & obj) const
  {
    return m_min == obj.m_min && m_max == obj.m_max;
  }
  bool operator != (Box2D const & obj) const
  {
    return !operator==(obj);
  }

  // Check boxes intersection
  bool IntersectBox(Box2D const & obj) const
  {
    // B1 is left of B2
    if (m_max.x() < obj.boxMin().x())
      return false;
    // B1 is right of B2
    if (m_min.x() > obj.boxMax().x())
      return false;
    // B1 is above B2
    if (m_max.y() < obj.boxMin().y())
      return false;
    // B1 is below B2
    if (m_min.y() > obj.boxMax().y())
      return false;
    return true;
  }
private:
  // Swap points if min > max
  void PointSwap()
  {
    if (m_max < m_min)
      std::swap(m_min, m_max);

    try
    {
      if (m_min.x() == m_max.x() || m_min.y() == m_max.y())
        throw std::invalid_argument("Min and Max angles should be different!");
    }
    catch (std::exception const & ex)
    {
      LOG(LOG_ERROR) << ex.what();
      m_min = {0, 0};
      m_max = {1, 1};
    }
  }

  Point2D m_min {0, 0};
  Point2D m_max {1, 1};
};

inline std::ostream & operator << (std::ostream & os, Box2D const & obj)
{
  os << "Box2D { " << obj.boxMin() << ", " << obj.boxMax() << " }";
  return os;
}
