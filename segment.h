#pragma once
#ifndef GEOMETRY__SEGMENT_H_
#define GEOMETRY__SEGMENT_H_
#include "ishape.h"
#include <string>
namespace geometry {
class Segment : public IShape {
 public:
  Point q;
  Point p;
  Segment(const Point& a, const Point& b);
  IShape& Move(const Vector& a) override;
  bool ContainsPoint(const Point& a) const override;
  bool CrossesSegment(const Segment& a) const override;
  IShape* Clone() const override;
  std::string ToString() const override;
};
}  // namespace geometry
#endif
