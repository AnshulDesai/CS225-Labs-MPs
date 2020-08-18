#include "cs225/PNG.h"
using cs225::PNG;

#include "cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <string>



void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  PNG original, rotated;
  original.readFromFile(inputFile);
  rotated.readFromFile(inputFile);
  unsigned int width = original.width();
  unsigned int height = original.height();
  for (unsigned int x = 0; x < width; x++) {
    for (unsigned int y = 0; y < height; y++) {
      unsigned rotx = (width - 1) - x;
      unsigned roty = (height - 1) - y;
      HSLAPixel & origpixel = original.getPixel(x, y);
      HSLAPixel & rotpixel = rotated.getPixel(rotx, roty);
      rotpixel = origpixel;
    }
  }
  rotated.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  // TODO: Part 3
  double starthue = 176.0;
  double endhue = 253.0;
  double hueval = starthue;
  double jump = (endhue - starthue) / height;
  for (unsigned int x = 0; x < width; x++) {
    hueval = starthue;
    for (unsigned int y = 0; y < height; y++) {
      HSLAPixel & origpixel = png.getPixel(x, y);
      origpixel.a = 1.0;
      origpixel.l = 0.5;
      origpixel.s = 1.0;
      origpixel.h = hueval;
      hueval += jump;
    }
  }
  return png;
}
