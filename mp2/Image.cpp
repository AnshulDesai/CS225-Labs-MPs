#include <iostream>
#include <cmath>
#include <cstdlib>

#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

void Image::lighten() {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.l += 0.1;
      if (pixel.l > 1.0) {
        pixel.l = 1.0;
      }
    }
  }
}

void Image::lighten(double amount) {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.l += amount;
      if (pixel.l > 1.0) {
        pixel.l = 1.0;
      }
    }
  }
}

void Image::darken() {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.l -= 0.1;
      if (pixel.l < 0.0) {
        pixel.l = 0.0;
      }
    }
  }
}

void Image::darken(double amount) {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.l -= amount;
      if (pixel.l < 0.0) {
        pixel.l = 0.0;
      }
    }
  }
}

void Image::saturate() {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.s += 0.1;
      if (pixel.s > 1.0) {
        pixel.s = 1.0;
      }
    }
  }
}

void Image::saturate(double amount) {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.s += amount;
      if (pixel.s > 1.0) {
        pixel.s = 1.0;
      }
    }
  }
}

void Image::desaturate() {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.s -= 0.1;
      if (pixel.s < 0.0) {
        pixel.s = 0.0;
      }
    }
  }
}

void Image::desaturate(double amount) {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.s -= amount;
      if (pixel.s < 0.0) {
        pixel.s = 0.0;
      }
    }
  }
}

void Image::grayscale() {
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.s = 0;
    }
  }
}

void Image::rotateColor(double degrees) {
  double result = fmod(degrees, 360.0);
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.h += result;
      if (pixel.h > 360.0) {
        pixel.h -= 360.0;
      }
      else if (pixel.h < 0.0) {
        pixel.h += 360;
      }
    }
  }
}

void Image::illinify() {
  double orange = 11;
  double blue = 216;
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      if (pixel.h >= 113.5 && pixel.h <= 293.5)
	{
	  pixel.h = blue;
	}
      else
	{
	  pixel.h = orange;
	}
    }
  }
}

void Image::scale(double factor) {
  writeToFile("tempScale.png");
  unsigned newWidth = width() * factor;
  unsigned newHeight = height() * factor;
  PNG * origImage = new PNG(width(), height());
  origImage->readFromFile("tempScale.png");
  resize(newWidth, newHeight);
  double scaleMaxX = factor;
  double scaleMaxY = factor;
  for (unsigned x = 0; x < origImage->width(); x++) {
    for(unsigned y = 0; y < origImage->height(); y++) {
      HSLAPixel & origPixel = origImage->getPixel(x, y);
      for(double scalex = x * factor; scalex < scaleMaxX; scalex += 1) {
        for(double scaley = y * factor; scaley < scaleMaxY; scaley += 1) {
          HSLAPixel & newPixel = getPixel(scalex, scaley);
          newPixel = origPixel;
        }
      }
      scaleMaxY = scaleMaxY + factor;
    }
    scaleMaxX = scaleMaxX + factor;
    scaleMaxY = factor;
  }
}

void Image::scale(unsigned w, unsigned h) {
  double widthFactor = w / width();
  double heightFactor = h / height();
  scale(widthFactor);
}
