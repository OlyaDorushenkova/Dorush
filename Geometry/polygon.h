#pragma once
#ifndef MAIN_CPP__POLYGON_H_
#define MAIN_CPP__POLYGON_H_
#include "ishape.h"
#include <vector>
namespace geometry {
class Polygon : public IShape {
 public:
  int size;
  std::vector<Point> a;
  explicit Polygon(const std::vector<Point>& b);
  IShape& Move(const Vector& b) override;
  bool ContainsPoint(const Point& b) const override;
  bool CrossesSegment(const Segment& b) const override;
  IShape* Clone() const override;
  std::string ToString() const override;
};
}  // namespace geometry
#endif  // MAIN_CPP__POLYGON_H_
