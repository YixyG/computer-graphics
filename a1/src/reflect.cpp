#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
  
  //traverse every row
  for (int r = 0; r < height; r++)
  {
	  // traverse first half of columns
	  for (int i = 0; i < width / 2 + 1; i++)
	  {
		  int j = width - i - 1;
		  //traverse number of channels
		  for (int channel = 0; channel < num_channels; channel++)
		  {
			  reflected[num_channels * (width * r + i) + channel] = input[num_channels * (width * r + j) + channel];
			  reflected[num_channels * (width * r + j) + channel] = input[num_channels * (width * r + i) + channel];
		  }
	  }
  }
  
}
