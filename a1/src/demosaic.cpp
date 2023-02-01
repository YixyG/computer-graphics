#include "demosaic.h"
#define DEMOSAIC_H
#include <vector>

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  
  for (int row = 0; row < height; row++)
  {
	  // clr_ind = 0 if on even index rows (blue/green)
	  // clr_ind = 1 if on odd index rows (red/green)
	  int clr_ind = 0;
	  if (row % 2 == 1) {
		  clr_ind = 1;
	  }
		  
	  for (int col = 0; col < width; col++) {
		  int i = row * width + col;				//index in mosaic
		  int r = 0, g = 0, b = 0;
		  // index of surrounding pixels
		  int topL = i - width - 1;
		  int top = i - width;
		  int topR = i - width + 1;
		  int botL = i + width - 1;
		  int bot = i + width;
		  int botR = i + width + 1;
		  int left = i - 1;
		  int right = i + 1;

		  int channel = clr_ind + (col + 1) % 2;	// blue = 0, green = 1, red = 2
		  
		  // get b
		  // blue pixel, itself
		  if (channel == 0) {
			  b = bayer[i];	
		  }

		  // green pixel, vertical or horizontal
		  else if (channel == 1) {			// green channel
			  int count = 0;				// count the number of left and right blue channels
			  if (row % 2 == 1) {				// a green channel on odd rows, BGBG...
				  if (row > 0)
				  {
					  b += bayer[top];
					  count++;
				  }
				  if (row < height - 1)		// check if green is on lowest row
				  {
					  b += bayer[bot];
					  count++;
				  }
				  b = b / count;			// count is either 1 or 2
			  }
			  else if (row % 2 == 0) {		// a green channel on even rows, blue is vertical
				  if (col > 0)
				  {
					  b += bayer[left];
					  count++;
				  }
				  if (col < width - 1)		// check if green is on right most column
				  {
					  b += bayer[right];
					  count++;
				  }
				  b = b / count;			// count is either 1 or 2
			  }
		  }

		  //red pixel, 4 corners if (channel == 2)
		  else {
			  int count = 0;
			  if (row > 0 && col > 0) {			// add top left blue value
				  b += bayer[topL];
				  count++;
			  }
			  if (row < height - 1 && col > 0) {
				  b += bayer[botL];			// add bottom left blue value
				  count++;
			  }
			  if (row > 0 && col < width - 1) {
				  b += bayer[topR];			// add top right blue value
				  count++;
			  }
			  if (row < height - 1 && col < width - 1) {
				  b += bayer[botR];			// add bottom right blue value
				  count++;
			  }
			  b = b / count;
		  }
		  
		  // get g
		  // green pixel, itself
		  if (channel == 1) {
			  g = bayer[i];
		  }

		  // red or blue pixels, both vertical and horizontal
		  else {
			  int count = 0;
			  if (row > 0) {			// top
				  g += bayer[top];
				  count++;
			  }
			  if (row < height - 1) {	// bottom
				  g += bayer[bot];
				  count++;
			  }
			  if (col > 0) {
				  g += bayer[left];
				  count++;
			  }
			  if (col < width - 1) {
				  g += bayer[right];
				  count++;
			  }
			  g = g / count;
		  }
		  
		  // get r
		  // red pixel, itself
		  if (channel == 2) {
			  r = bayer[i];
		  }

		  // green pixel, vertical or horizontal
		  else if (channel == 1) {			// green channel
			  int count = 0;				// count the number of left and right blue channels
			  if (row % 2 == 1) {			// a green channel on odd rows, BGBG...
				  if (col > 0)
				  {
					  r += bayer[left];
					  count++;
				  }
				  if (col < width - 1)		// check if green is on right most column
				  {
					  r += bayer[right];
					  count++;
				  }
				  r = r / count;			// count is either 1 or 2
			  }
			  else if (row % 2 == 0) {		// a green channel on even rows, red is vertical
				  if (row > 0)
				  {
					  r += bayer[top];
					  count++;
				  }
				  if (row < height - 1)		// check if green is on lowest row
				  {
					  r += bayer[bot];
					  count++;
				  }
				  r = r / count;			// count is either 1 or 2
			  }
		  }

		  //blue pixel, 4 corners if (channel == 0) 
		  else {
			  int count = 0;
			  if (row > 0 && col > 0) {			// add top left red value
				  r += bayer[topL];
				  count++;
			  }
			  if (row < height - 1 && col > 0) {
				  r += bayer[botL];			// add bottom left red value
				  count++;
			  }
			  if (row > 0 && col < width - 1) {
				  r += bayer[topR];			// add top right red value
				  count++;
			  }
			  if (row < height - 1 && col < width - 1) {
				  r += bayer[botR];			// add bottom right red value
				  count++;
			  }
			  r = r / count;
		  }
		  
		  rgb[3 * i] = r;
		  rgb[3 * i + 1] = g;
		  rgb[3 * i + 2] = b;
	  }
  }
  
/*
for (int row = 0; row < height; ++row) {
	int offset = row % 2 ? 0 : 1;
	for (int col = 0; col < width; ++col) {
		int index = width * row + col;      // Index in mosaic
		int channel = offset + (col % 2);   // Color channel of mosaic pixel

		// Get indexes of 8 neighbouring pixels
		int top_left = index - (width + 1),
			top = index - width,
			top_right = index - (width - 1),
			left = index - 1,
			right = index + 1,
			bot_left = index + (width - 1),
			bot = index + width,
			bot_right = index + (width + 1);

		int r, g, b;

		// Get value for r
		if (channel == 0) {
			// Red channel. Just take value.
			r = bayer[index];
		}
		else if (channel == 1) {
			// Green channel
			r = 0;
			int count = 0;
			if (row % 2 == 0) {
				// Red is vertically up and down
				if (row > 0) {
					r += bayer[top];
					count++;
				}
				if (row < height - 1) {
					r += bayer[bot];
					count++;
				}

				if (count > 0)
					r /= count;
			}
			else {
				// Red is horizontally left and right
				if (col > 0) {
					r += bayer[left];
					count++;
				}
				if (col < width - 1) {
					r += bayer[right];
					count++;
				}

				if (count > 0)
					r /= count;
			}
		}
		else {
			// Blue channel. Red is in four corners.
			r = 0;
			int count = 0;
			if (row > 0 && col > 0) {
				r += bayer[top_left];
				count++;
			}
			if (row < height - 1 && col > 0) {
				r += bayer[bot_left];
				count++;
			}
			if (row > 0 && col < width - 1) {
				r += bayer[top_right];
				count++;
			}
			if (row < height - 1 && col < width - 1) {
				r += bayer[bot_right];
				count++;
			}

			if (count > 0)
				r /= count;
		}

		// Get value for g
		if (channel == 1) {
			// Green channel. Just take value.
			g = bayer[index];
		}
		else {
			// Red or Blue channel. Green is on four sides
			g = 0;
			int count = 0;
			if (row > 0) {
				g += bayer[top];
				count++;
			}
			if (row < height - 1) {
				g += bayer[bot];
				count++;
			}
			if (col > 0) {
				g += bayer[left];
				count++;
			}
			if (col < width - 1) {
				g += bayer[right];
				count++;
			}

			if (count > 0)
				g /= count;
		}

		// Get value for b
		if (channel == 2) {
			// Blue channel. Just take value.
			b = bayer[index];
		}
		else if (channel == 1) {
			// Green channel
			b = 0;
			int count = 0;
			if (row % 2 == 1) {
				// Blue is vertically up and down
				if (row > 0) {
					b += bayer[top];
					count++;
				}
				if (row < height - 1) {
					b += bayer[bot];
					count++;
				}

				if (count > 0)
					b /= count;
			}
			else {
				// Blue is horizontally left and right
				if (col > 0) {
					b += bayer[left];
					count++;
				}
				if (col < width - 1) {
					b += bayer[right];
					count++;
				}

				if (count > 0)
					b /= count;
			}
		}
		else {
			// Red channel. Blue is in four corners.
			b = 0;
			int count = 0;
			if (row > 0 && col > 0) {
				b += bayer[top_left];
				count++;
			}
			if (row < height - 1 && col > 0) {
				b += bayer[bot_left];
				count++;
			}
			if (row > 0 && col < width - 1) {
				b += bayer[top_right];
				count++;
			}
			if (row < height - 1 && col < width - 1) {
				b += bayer[bot_right];
				count++;
			}

			if (count > 0)
				b /= count;
		}

		// Got all values. Put in output array.
		rgb[3 * index] = r;
		rgb[3 * index + 1] = g;
		rgb[3 * index + 2] = b;

	}
}
*/
}
