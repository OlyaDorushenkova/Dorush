#pragma once
#ifndef GEOMETRY__ISHAPE_H_
#define GEOMETRY__ISHAPE_H_
#include <string>
namespace geometry {
class Vector;
class Segment;
class Point;
class Line;
class Ray;
class Polygon;
class Circle;
class IShape {
 public:
  virtual IShape& Move(const Vector& a) = 0;
  virtual bool ContainsPoint(const Point& a) const = 0;
  virtual bool CrossesSegment(const Segment& a) const = 0;
  virtual IShape* Clone() const = 0;
  virtual std::string ToString() const = 0;
  virtual ~IShape() = default;
};
}  // namespace geometry
#endif
