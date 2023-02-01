#include "rgb_to_hsv.h"
#include <algorithm>
#include <cmath>

/*
Reference
https://en.wikipedia.org/wiki/HSL_and_HSV
Slide 10 from Week 1 Raster Image
*/
void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  double M = std::max({ r, g, b }); // Max channel value
  double m = std::min({ r, g, b }); // Min channel value
  double C = M - m;   // Chroma

  // find value of h(H)
  if (C == 0)
	  h = 0;
  else if (M == r) 
	  // note: % only applies to int
	  h = std::fmod((g - b) / C, 6);
  else if (M == g)
	  h = (b - r) / C + 2;
  else if (M == b)
	  h = (r - g) / C + 4;
	
  h *= 60;

  // h in degrees [0,360)
  if (h < 0) {
	  h = std::fmod(h, 360);
	  h += 360;
  }

  // find value of v: V=R
  v = M;

  // find value of s: S=(R-B)/R
  if (M == 0)
	  s = 0;
  else
	  s = C / M;
	  
}
