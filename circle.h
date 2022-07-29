#pragma once
#ifndef MAIN_CPP__CIRCLE_H_
#define MAIN_CPP__CIRCLE_H_
namespace geometry {
class Circle : public IShape {
 public:
  Point c;
  int r;
  Circle(const Point& a, int b);
  IShape& Move(const Vector& a) override;
  bool ContainsPoint(const Point& a) const override;
  bool CrossesSegment(const Segment& a) const override;
  IShape* Clone() const override;
  std::string ToString() const override;
};
}  // namespace geometry
#endif  // MAIN_CPP__CIRCLE_H_
