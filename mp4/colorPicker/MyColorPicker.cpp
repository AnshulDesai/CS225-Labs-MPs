#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

MyColorPicker::MyColorPicker(double increment)
  : hue_(173), increment_(increment), forward_(true) { }

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel pixel(hue_, 1, 0.5);

  if (forward_) {
    hue_ += increment_;
  }
  else {
    hue_ -= increment_;
  }
  if (hue_ >= 201) {
    forward_ = false;
  }
  if (hue_ <= 173) {
    forward_ = true;
  }
  return pixel;
}
