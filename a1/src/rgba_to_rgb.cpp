#include "rgba_to_rgb.h"

void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(height*width*3);
  //traverse through rgba, skip index of multiples of 4

  int index_rgb = 0;
  for (int index_rgba = 0; index_rgba < rgba.size(); index_rgba++) {
	  if ((index_rgba+1) % 4 != 0) {
		  rgb[index_rgb++] = rgba[index_rgba];
	  }
  }
}
