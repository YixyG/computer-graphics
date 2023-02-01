#include "over.h"

/*
Reference
https://en.wikipedia.org/wiki/Alpha_compositing
*/
void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());
  
  for (int i = 0; i < width * height * 4; i += 4)
  {
	  // Alpa values a_a & a_b & a_o for ith pixel in A, B and overlay
	  double alpha_A = A[i + 3] / 255.0;
	  double alpha_B = B[i + 3] / 255.0;
	  double alpha_o = alpha_A + alpha_B * (1.0 - alpha_A);
	  for (int j= 0; j < 3; j++)
	  {
		  C[i + j] = (unsigned char) (((double) A[i + j] * alpha_A + (double) B[i + j] * alpha_B * (1.0 - alpha_A)) / alpha_o);
	  }// alpha
	  C[i + 3] = (unsigned char)(alpha_o * 255);
  }
  
}
