#pragma once

#include <iostream>
#include "point2d.hpp"

class Box2D: public Point2D
{
public:
  // Constructors
  Box2D() = default;
  Box2D(float x1, float y1, float x2, float y2)
    : m_min({x1, y1}), m_max({x2, y2})
  { PointSwap(); }
  Box2D(Point2D p1, Point2D p2)
    : m_min(p1), m_max(p2)
  { PointSwap(); }

  // Copy constructor
  Box2D(Box2D const &obj)
    : m_min(obj.m_min), m_max(obj.m_max)
  { PointSwap(); }

  // Getters
  Point2D &p1() { return m_min; }
  Point2D &p2() { return m_max; }
  Point2D const &p1() const { return m_min; }
  Point2D const &p2() const { return m_max; }

  // Logical operators
  bool operator == (Box2D const &obj) const
  {
    return m_min == obj.m_min && m_max == obj.m_max;
  }
  bool operator != (Box2D const &obj) const
  {
    return !operator==(obj);
  }

  // Functionality
  bool IntersectBox(Box2D const &obj) const
  {
    return m_min.x() < obj.p2().x()
      && m_max.x() > obj.p1().x()
      && m_min.y() < obj.p2().y()
      && m_max.y() > obj.p1().y();
  }
private:
  void PointSwap() {
    if (m_max < m_min)
      std::swap(m_min, m_max);
  }

  Point2D m_min {0, 0};
  Point2D m_max {1, 1};
};

std::ostream &operator << (std::ostream &os, Box2D const &obj)
{
  os << "Box2D { " << obj.p1() << ", " << obj.p2() << " }";
  return os;
}