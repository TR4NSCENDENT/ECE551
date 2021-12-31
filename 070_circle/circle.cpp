#include "circle.hpp"
#include <cmath>

double Circle::intersectionArea(const Circle & otherCircle) {
  double d = p.distanceFrom(otherCircle.p); //distance between centers
  const double & R = otherCircle.r; //for simplicity
  if (d >= R + r) { return 0; } //no intersection
  if (R == 0 || r == 0) { return 0; } //no area
  if (R < r) {
    if (d <= r - R) {
      return M_PI * R * R;
    }
  }
  else{
    if (d <= R - r) {
      return M_PI * r * r;
    }
  }
  //detailed steps for calculation below can be found at
  //https://mathworld.wolfram.com/Circle-CircleIntersection.html
  double x = (d * d - r * r + R * R) / (2 * d);
  double temp = d * d - r * r + R * R;
  temp *= temp;
  double a_dot_d = std::sqrt(4 * d * d * R * R - temp);
  double seg1 = r * r * std::acos((d - x) / r);
  double seg2 = R * R * std::acos(x / R);
  double ans = seg1 + seg2 - a_dot_d / 2;
  return ans;
}
