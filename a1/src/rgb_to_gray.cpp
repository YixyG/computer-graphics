#include "rgb_to_gray.h"

void rgb_to_gray(
    const std::vector<unsigned char>& rgb,
    const int width,
    const int height,
    std::vector<unsigned char>& gray)
{
    gray.resize(height * width);

    // weighted average
    double r_weight = 0.2126, g_weight = 0.7152, b_weight = 0.0722;
    
    for (int i = 0; i < width * height * 3; i += 3) {
        // RGB values in each pixel of input(rgb)
        double r = rgb[i], g = rgb[i + 1], b = rgb[i + 2];
        // grayscale is 1-channel
        gray[i / 3] = (unsigned char)(r * r_weight + g * g_weight + b * b_weight);
    }
    
}


