#include <string>
#include <vector>
#include "../vector.h"
#include "../point.h"
#include "../segment.h"
#include "../line.h"
#include "../ray.h"
#include "../circle.h"
#include "../polygon.h"
namespace geometry {
Vector::Vector(const int &a, const int &b) {
  x = a;
  y = b;
}
Vector::Vector() {
  x = 0;
  y = 0;
}
Vector Vector::operator+() const {
  return {x, y};
}
Vector Vector::operator-() const {
  return {-x, -y};
}
Vector &Vector::operator+=(Vector &other) {
  x += other.x;
  y += other.y;
  return *this;
}
Vector &Vector::operator-=(Vector &other) {
  x -= other.x;
  y -= other.y;
  return *this;
}
Vector &Vector::operator*=(int a) {
  x *= a;
  y *= a;
  return *this;
}
Vector &Vector::operator/=(int a) {
  x /= a;
  y /= a;
  return *this;
}
Vector operator+(const Vector &left, const Vector &right) {
  Vector ans(0, 0);
  ans.x = left.x + right.x;
  ans.y = left.y + right.y;
  return ans;
}
Vector operator-(const Vector &left, const Vector &right) {
  Vector ans(0, 0);
  ans.x = left.x - right.x;
  ans.y = left.y - right.y;
  return ans;
}
Vector operator*(const Vector &left, const int &a) {
  Vector ans(0, 0);
  ans.x = left.x * a;
  ans.y = left.y * a;
  return ans;
}
Vector operator/(const Vector &left, const int &a) {
  Vector ans(0, 0);
  ans.x = left.x / a;
  ans.y = left.y / a;
  return ans;
}
bool operator==(const Vector &left, const Vector &right) {
  return (left.x == right.x && left.y == right.y);
}
bool operator!=(const Vector &left, const Vector &right) {
  return !(left.x == right.x && left.y == right.y);
}
Point::Point() {
  x = 0;
  y = 0;
}
Point::Point(const int &a, const int &b) {
  x = a;
  y = b;
}
IShape &Point::Move(const Vector &a) {
  x += a.x;
  y += a.y;
  return *this;
}
bool Point::ContainsPoint(const Point &a) const {
  return (a.x == x && a.y == y);
}
bool Point::CrossesSegment(const Segment &a) const {
  Vector v1(x - a.q.x, y - a.q.y);
  Vector v2(a.p.x - x, a.p.y - y);
  return (v1.x * v2.y - v1.y * v2.x == 0 && v1.x * v2.x + v1.y * v2.y >= 0);
}
IShape *Point::Clone() const {
  return new Point(x, y);
}
std::string Point::ToString() const {
  std::string s = "Point(";
  s += std::to_string(x);
  s += ", ";
  s += std::to_string(y);
  s += ")";
  return s;
}
Segment::Segment(const Point &a, const Point &b) {
  q = a;
  p = b;
}
IShape &Segment::Move(const Vector &a) {
  q.Move(a);
  p.Move(a);
  return *this;
}
bool Segment::ContainsPoint(const Point &a) const {
  return a.CrossesSegment(*this);
}
bool Segment::CrossesSegment(const Segment &a) const {
  Line l(q, p);
  Line la(a.q, a.p);
  int k = 0;
  if (((a.q.x - q.x) * (q.x - a.p.x) >= 0 || (a.q.x - p.x) * (p.x - a.p.x) >= 0 || (a.q.x - q.x) * (p.x - a.q.x) >= 0 ||
       (a.p.x - q.x) * (p.x - a.p.x) >= 0) &&
      ((a.q.y - q.y) * (q.y - a.p.y) >= 0 || (a.q.y - p.y) * (p.y - a.p.y) >= 0 || (a.q.y - q.y) * (p.y - a.q.y) >= 0 ||
       (a.p.y - q.y) * (p.y - a.p.y) >= 0)) {
    k = 1;
  }
  return (k == 1 && l.CrossesSegment(a) && la.CrossesSegment(*this));
}
IShape *Segment::Clone() const {
  return new Segment(q, p);
}
std::string Segment::ToString() const {
  std::string s = "Segment(" + q.ToString() + ", " + p.ToString() + ")";
  return s;
}
Line::Line(const int64_t &a, const int64_t &b, const int64_t &c) {
  A = a;
  B = b;
  C = c;
}
Line::Line(const Point &a, const Point &b) {
  A = a.y - b.y;
  B = b.x - a.x;
  C = a.x * b.y - a.y * b.x;
}
IShape &Line::Move(const Vector &a) {
  C -= (A * a.x + B * a.y);
  return *this;
}
bool Line::ContainsPoint(const Point &a) const {
  return (A * a.x + B * a.y + C == 0);
}
bool Line::CrossesSegment(const Segment &a) const {
  long long int first = (A * a.q.x + B * a.q.y + C);
  long long int second = (A * a.p.x + B * a.p.y + C);
  return (first * second <= 0);
}
IShape *Line::Clone() const {
  return new Line(A, B, C);
}
std::string Line::ToString() const {
  std::string s = "Line(" + std::to_string(A) + ", " + std::to_string(B) + ", " + std::to_string(C) + ")";
  return s;
}
Ray::Ray(const Point &a, const Point &b) {
  q = a;
  Vector e(b.x - a.x, b.y - a.y);
  v = e;
}
Ray::Ray(const Point &a, const Vector &b) {
  q = a;
  v = b;
}
IShape &Ray::Move(const Vector &a) {
  q.Move(a);
  return *this;
}
bool Ray::ContainsPoint(const Point &a) const {
  Vector d(a.x - q.x, a.y - q.y);
  long long int first = v.x * d.x + v.y * d.y;
  long long int second = v.x * d.y - v.y * d.x;
  return (first >= 0 && second == 0);
}
bool Ray::CrossesSegment(const Segment &a) const {
  if (!a.ContainsPoint(q)) {
    Point q1(q.x + v.x, q.y + v.y);
    Line l(q, q1);
    Vector Po(q.x - a.q.x, q.y - a.q.y);
    Vector Qp(a.p.x - a.q.x, a.p.y - a.q.y);
    long long int first = (v.x * Qp.y - v.y * Qp.x);
    long long int second = (Po.x * Qp.y - Po.y * Qp.x);
    return (first * second <= 0 && l.CrossesSegment(a));
  }
  return true;
}
IShape *Ray::Clone() const {
  return new Ray(q, v);
}
std::string Ray::ToString() const {
  std::string s = "Ray(" + q.ToString() + ", ";
  s += "Vector(" + std::to_string(v.x) + ", " + std::to_string(v.y) + "))";
  return s;
}
Polygon::Polygon(const std::vector<Point> &b) {
  size = b.size();
  for (int i = 0; i < size; i++) {
    a.push_back(b[i]);
  }
}
IShape &Polygon::Move(const Vector &b) {
  for (int i = 0; i < size; i++) {
    a[i].Move(b);
  }
  return *this;
}
bool Polygon::ContainsPoint(const Point &b) const {
  Vector v(1, 0);
  int k = 0;
  Ray r(b, v);
  for (int i = 0; i < size - 1; i++) {
    Segment s(a[i], a[i + 1]);
    if (b.CrossesSegment(s)) {
      return true;
    }
    if (r.CrossesSegment(s)) {
      if (a[i].y == b.y && a[i].y > a[i + 1].y) {
        k++;
      } else if (a[i + 1].y == b.y && a[i + 1].y > a[i].y) {
        k++;
      } else if (a[i + 1].y != b.y && a[i].y != b.y) {
        k++;
      }
    }
  }
  int i = size - 1;
  Segment s(a[i], a[0]);
  if (b.CrossesSegment(s)) {
    return true;
  }
  if (r.CrossesSegment(s)) {
    if (a[i].y == b.y && a[i].y > a[0].y) {
      k++;
    } else if (a[0].y == b.y && a[0].y > a[i].y) {
      k++;
    } else if (a[0].y != b.y && a[i].y != b.y) {
      k++;
    }
  }
  return (k % 2);
}
bool Polygon::CrossesSegment(const Segment &b) const {
  for (int i = 0; i < size - 1; i++) {
    Segment s(a[i], a[i + 1]);
    if (s.CrossesSegment(b)) {
      return true;
    }
  }
  Segment s(a[size - 1], a[0]);
  if (s.CrossesSegment(b)) {
    return true;
  }
  return false;
}
IShape *Polygon::Clone() const {
  return new Polygon(a);
}
std::string Polygon::ToString() const {
  std::string s = "Polygon(";
  for (int i = 0; i < size; i++) {
    s += "Point(" + std::to_string(a[i].x);
    s += ", " + std::to_string(a[i].y) + ")";
    if (i == size - 1) {
      break;
    }
    s += ", ";
  }
  s += ")";
  return s;
}
Circle::Circle(const Point &a, int b) {
  c = a;
  r = b;
}
IShape &Circle::Move(const Vector &a) {
  c.Move(a);
  return *this;
}
bool Circle::ContainsPoint(const Point &a) const {
  return r * r >= (a.x - c.x) * (a.x - c.x) + (a.y - c.y) * (a.y - c.y);
}
bool Circle::CrossesSegment(const Segment &a) const {
  Vector qp(a.p.x - a.q.x, a.p.y - a.q.y);
  Vector pq = -qp;
  Vector qc(c.x - a.q.x, c.y - a.q.y);
  Vector pc(c.x - a.p.x, c.y - a.p.y);
  Line l(a.q, a.p);
  if (r * r > (a.p.x - c.x) * (a.p.x - c.x) + (a.p.y - c.y) * (a.p.y - c.y)) {
    if (r * r > (a.q.x - c.x) * (a.q.x - c.x) + (a.q.y - c.y) * (a.q.y - c.y)) {
      return false;
    }
  }
  if (qp.x * qc.x + qp.y * qc.y <= 0) {
    long long int f1 = r * r;
    long long int s1 = (a.q.x - c.x) * (a.q.x - c.x) + (a.q.y - c.y) * (a.q.y - c.y);
    return (f1 >= s1);
  }
  if (pq.x * pc.x + pq.y * pc.y <= 0) {
    long long int f2 = r * r;
    long long int s2 = (a.p.x - c.x) * (a.p.x - c.x) + (a.p.y - c.y) * (a.p.y - c.y);
    return (f2 >= s2);
  }
  long long int f = r * r * (l.A * l.A + l.B * l.B);
  long long int s = (l.A * c.x + l.B * c.y + l.C) * (l.A * c.x + l.B * c.y + l.C);
  return (f >= s);
}
IShape *Circle::Clone() const {
  return new Circle(c, r);
}
std::string Circle::ToString() const {
  std::string s = "Circle(" + c.ToString() + ", " + std::to_string(r) + ")";
  return s;
}
}  // namespace geometry
geometry::Vector operator-(const geometry::Point &a, const geometry::Point &b) {
  geometry::Vector v(a.x - b.x, a.y - b.y);
  return v;
}