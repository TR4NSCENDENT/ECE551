#include "point.hpp"
#include <cmath>

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  double dx = p.x - x;
  double dy = p.y - y;
  double ans = std::sqrt(dx * dx + dy * dy);
  return ans;
}
  
