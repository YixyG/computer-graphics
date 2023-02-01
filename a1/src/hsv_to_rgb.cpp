#include "hsv_to_rgb.h"
#include <algorithm>
#include <cmath>
/*
Reference
https://en.wikipedia.org/wiki/HSL_and_HSV
*/
void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{ 
  double C = v * s;   // Chroma
  double H = h / 60;  // H value
  double X = C * (1 - std::fabs(std::fmod(H, 2) - 1));  // Intermediate value

  // special case: H = 0
  if (H == 0) {
      r = 0;
      g = 0;
      b = 0;
  }
  else if (H < 1) {
      r = C;
      g = X;
      b = 0;
  }
  else if (H < 2) {
      r = X;
      g = C;
      b = 0;
  }
  else if (H < 3) {
      r = 0;
      g = C;
      b = X;
  }
  else if (H < 4) {
      r = 0;
      g = X;
      b = C;
  }
  else if (H < 5) {
      r = X;
      g = 0;
      b = C;
  }
  else {
      r = C;
      g = 0;
      b = X;
  }

  double m = v - C;
  r += m;
  g += m;
  b += m;
  
}
