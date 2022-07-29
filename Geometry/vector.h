#pragma once
#ifndef GEOMETRY_LIBRARY_H
#define GEOMETRY_LIBRARY_H
namespace geometry {
class Point;
class Vector {
 public:
  int x;
  int y;
  Vector();
  Vector(const int &x, const int &y);
  Vector operator+() const;
  Vector operator-() const;
  Vector &operator+=(Vector &other);
  Vector &operator-=(Vector &other);
  Vector &operator*=(int a);
  Vector &operator/=(int a);
};
Vector operator+(const Vector &left, const Vector &right);
Vector operator-(const Vector &left, const Vector &right);
Vector operator*(const Vector &left, const int &a);
Vector operator/(const Vector &left, const int &a);
bool operator==(const Vector &left, const Vector &right);
bool operator!=(const Vector &left, const Vector &right);
}  // namespace geometry
geometry::Vector operator-(const geometry::Point &a, const geometry::Point &b);
#endif  // GEOMETRY_LIBRARY_H
