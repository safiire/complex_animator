#include <color/color.h>

using namespace std;
using namespace glm;

vec3 complex_to_hsv(complex<double> z){
  const double e = 2.718281828459045;
  const double tau = 6.283185307179586;
  double w = arg(z);

  while(w < 0.0)
    w += tau;
  while(w >= tau)
    w -= tau;

  double hue = w / tau;

  double m = norm(z);
  double r0 = 0.0;
  double r1 = 1.0;

  while(m > r1){
    r0 = r1;
    r1 = r1 * e;
  }
  double r = (m - r0) / (r1 - r0);

  double p = r < 0.5 ? 2.0 * r : 2.0 * (1.0- r);
  double q = 1.0 - p;

  double p1 = 1.0 - q * q * q;
  double q1 = 1.0 - p * p * p;

  double sat = 0.4 + 0.6 * p1;
  double val = 0.6 + 0.4 * q1;

  return vec3(hue, sat, val);
}
