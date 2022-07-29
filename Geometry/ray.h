#pragma once
#ifndef MAIN_CPP__RAY_H_
#define MAIN_CPP__RAY_H_
#include "ishape.h"
namespace geometry {
class Ray : public IShape {
 public:
  Point q;
  Vector v;
  Ray(const Point& a, const Point& b);
  Ray(const Point& a, const Vector& b);
  IShape& Move(const Vector& a) override;
  bool ContainsPoint(const Point& a) const override;
  bool CrossesSegment(const Segment& a) const override;
  IShape* Clone() const override;
  std::string ToString() const override;
};
}  // namespace geometry
#endif  // MAIN_CPP__RAY_H_
