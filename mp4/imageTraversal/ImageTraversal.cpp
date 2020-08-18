#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  t = NULL;  // Default constructor which sets t to NULL
}

ImageTraversal::Iterator::Iterator(ImageTraversal & trav) {
  t = &trav;
  unsigned w = t->image_.width();
  unsigned h = t->image_.height();
  //std::cout << "Width: " << w << " Height: " << h << std::endl;
  flags_ = new bool * [h];
  for (unsigned row = 0; row < h; row++){
      flags_[row] = new bool[w];
  }
  for (unsigned row = 0; row < h; row++){
      for(unsigned col = 0; col < w; col++){
          flags_[row][col] = false;
      }
  }
  flags_[t->start_.y][t->start_.x] = true;
  curr = t->start_;
  t->add(t->start_);
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  unsigned w = this->t->image_.width();
  unsigned h = this->t->image_.height();
  HSLAPixel startPixel = this->t->image_.getPixel(this->t->start_.x,this->t->start_.y);

  curr = this->t->peek();
  this->t->pop();

  flags_[curr.y][curr.x] = true;

  // Right test
  if (curr.x + 1 < w) {
    HSLAPixel rightPixel = this->t->image_.getPixel(curr.x + 1, curr.y);
    if (!flags_[curr.y][curr.x + 1] && calculateDelta(startPixel, rightPixel) < this->t->tolerance_) {
      this->t->add(Point(curr.x + 1, curr.y));
      // std::cout << "Right:: x: " << curr.x + 1 << " y: " << curr.y << std::endl;
    }
  }

  // Down test
  if (curr.y + 1 < h) {
    HSLAPixel downPixel = this->t->image_.getPixel(curr.x, curr.y + 1);
    if (!flags_[curr.y + 1][curr.x] && calculateDelta(startPixel, downPixel) < this->t->tolerance_) {
      this->t->add(Point(curr.x, curr.y + 1));
      // std::cout << "Down:: x: " << curr.x << " y: " << curr.y + 1 << std::endl;
    }
  }

  // Left test
  if (curr.x > 0) {
    HSLAPixel leftPixel = this->t->image_.getPixel(curr.x - 1, curr.y);
    if (!flags_[curr.y][curr.x - 1] && calculateDelta(startPixel, leftPixel) < this->t->tolerance_) {
      this->t->add(Point(curr.x - 1, curr.y));
      // std::cout << "Left:: x: " << curr.x - 1 << " y: " << curr.y << std::endl;
    }
  }

  // Up test
  if (curr.y > 0) {
    HSLAPixel upPixel = this->t->image_.getPixel(curr.x, curr.y - 1);
    if ( !flags_[curr.y - 1][curr.x] && calculateDelta(startPixel, upPixel) < this->t->tolerance_) {
      this->t->add(Point(curr.x, curr.y - 1));
      // std::cout << "Up:: x: " << curr.x << " y: " << curr.y - 1 << std::endl;
    }
  }

  curr = this->t->peek();

  while(flags_[curr.y][curr.x] && !this->t->empty()) {
    this->t->pop();
    if(this->t->empty()){
      break;
    }
    else {
      curr = this->t->peek();
    }
  }

  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool thisEmpty = false;
  bool othEmpty = false;

  if (t == NULL) {
    thisEmpty = true;
  }
  if (other.t == NULL) {
    othEmpty = true;
  }

  if (thisEmpty == false) {
    thisEmpty = t->empty();
  }
  if (othEmpty == false) {
    othEmpty = other.t->empty();
  }

  if (thisEmpty && othEmpty) {
    return false;
  }
  else if ((!thisEmpty) && (!othEmpty)) {
    return (t != other.t);
  }
  else {
    return true;
  }
}
