#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());
  double r = 0, g = 0, b = 0;
  double h = 0, s = 0, v = 0;
  
  for (int i = 0; i < width * height * 3; i += 3) {
	  // covert each pair of rgb into intensity [0,1]
	  r = rgb[i] / 255.0;
	  g = rgb[i + 1] / 255.0;
	  b = rgb[i + 2] / 255.0;
		
	  // rgb to hsv
	  rgb_to_hsv(r, g, b, h, s, v);
	  h += shift;
	  // check if h in [0, 360)
	  if (h >= 360)
	  {
		  h -= 360;
	  }
	  if (h < 0)
	  {
		  h += 360;
	  }
	  //covert to rgb
	  hsv_to_rgb(h, s, v, r, g, b);
	  //covert each pair of intensity into normal rgb
	  shifted[i] = (unsigned char)(r * 255);
	  shifted[i + 1] = (unsigned char)(g * 255);
	  shifted[i + 2] = (unsigned char)(b * 255);
  }
  
}
