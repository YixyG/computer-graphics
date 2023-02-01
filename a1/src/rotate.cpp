#include "rotate.h"

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);
  
  // index of rotated
  int index = 0;
  // last column of input is first row of rotated
  for (int c = width; c > 0; c--) 
  {
	  for (int r = 0; r < height; r++) {
		  for (int i = 0; i < num_channels; i++)
		  {
			  rotated[index] = input[num_channels * (r * width + c - 1) + i];
			  index++;
		  }
	  }
  }
  
}
