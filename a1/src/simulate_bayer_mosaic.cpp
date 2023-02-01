#include "simulate_bayer_mosaic.h"

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  
  for (int r = 0; r < height; r++)
  {
	  int i = 0;
	  if (r % 2 == 0)
	  {
		  i++;
	  }
	  for (int c = 0; c < width; c++)
	  {
		  int bay_ind = r * width + c;
		  int bay_chn = c % 2 + i;
		  bayer[bay_ind] = rgb[3 * bay_ind + bay_chn];
	  }
  }
  
}
