
#pragma once
#ifndef GEOMETRY__POINT_H_
#define GEOMETRY__POINT_H_
#include "ishape.h"
#include <string>
namespace geometry {
class Point : public IShape {
 public:
  int x;
  int y;
  Point();
  Point(const int& x, const int& y);
  IShape& Move(const Vector& a) override;
  bool ContainsPoint(const Point& a) const override;
  bool CrossesSegment(const Segment& a) const override;
  IShape* Clone() const override;
  std::string ToString() const override;
};
}  // namespace geometry
#endif
