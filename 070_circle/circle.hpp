#include "point.hpp"

class Circle {
private:
  Point p;
  const double r;
public:
  Circle(Point init_p, double init_r): p(init_p), r(init_r) {}
  void move(double dx, double dy) { p.move(dx, dy); }
  double intersectionArea(const Circle & otherCircle);
};
