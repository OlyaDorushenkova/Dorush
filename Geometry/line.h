#pragma once
#ifndef MAIN_CPP__LINE_H_
#define MAIN_CPP__LINE_H_
#include "ishape.h"
#include <string>
namespace geometry {
class Line : public IShape {
 public:
  int64_t A;
  int64_t B;
  int64_t C;
  Line(const int64_t& a, const int64_t& b, const int64_t& c);
  Line(const Point& a, const Point& b);
  IShape& Move(const Vector& a) override;
  bool ContainsPoint(const Point& a) const override;
  bool CrossesSegment(const Segment& a) const override;
  IShape* Clone() const override;
  std::string ToString() const override;
};
}  // namespace geometry
#endif  // MAIN_CPP__LINE_H_
