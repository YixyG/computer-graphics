
#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

/* Reference
https://en.wikipedia.org/wiki/Netpbm
https://stackoverflow.com/questions/28896001/read-write-to-ppm-image-file-c
*/
bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");
  
  std::ofstream ppm_file(filename);
  
  // check if file is closed
  if (!ppm_file.is_open()) {
      // message to stdout, add a new line and flush
      std::cout << "Failed to open file: " << filename << std::endl;
      return false;
  }

  // ASCII P3
  ppm_file << "P3"  << "\n" 
      << width      << " "
      << height     << "\n"
      << 255        << "\n"
      ;

  for (size_t i = 0; i < width * num_channels * height; ++i) {
      ppm_file << (int) data[i];    //unsigned char to unsigned int?

      // grayscale, repeat channel value two more times
      if (num_channels == 1)
          ppm_file << " " << (unsigned int)data[i] << " " << (unsigned int)data[i];

      if ((i + 1) % (width * num_channels) == 0)
          ppm_file << std::endl;    // next row
      else if ((i + 1) % num_channels == 0)
          ppm_file << "  ";   // Whitespace between pixels
      else
          ppm_file << " ";    // Whitespace between channels

  }

  // Close file
  ppm_file.close(); 
  return true;
  
}
