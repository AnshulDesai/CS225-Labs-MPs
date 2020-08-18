#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 *
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  img_ = new PNG(png);
  img2_ = new PNG(png);
}

/**
 * Adds a flood fill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 *
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  for (ImageTraversal::Iterator it = traversal.begin(); it != traversal.end(); ++it) {
    unsigned x = (*it).x;
    unsigned y = (*it).y;
    points_.push_back(Point(x, y));
    img2_->getPixel(x, y) = colorPicker.getColor(x, y);
  }
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 *
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 *
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 *
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  unsigned fCount = 0;
  /** @todo [Part 2] */
  for (auto it = points_.begin(); it != points_.end(); ++it) {
    unsigned x = (*it).x;
    unsigned y = (*it).y;
    if (fCount > points_.size()) {
      animation.addFrame(*img_);
    }
    else if (fCount == frameInterval * animation.frameCount()) {
      animation.addFrame(*img_);
    }
    fCount++;
    img_->getPixel(x, y) = img2_->getPixel(x, y);
  }
  animation.addFrame(*img_);
  return animation;
}
