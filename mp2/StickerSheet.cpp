#include <iostream>
#include "StickerSheet.h"

using namespace std;

namespace cs225 {
  StickerSheet::StickerSheet(const Image & background, unsigned max) {
    maxStickers_ = max;
    stickerCount_ = 0;
    xIndex = new unsigned int[maxStickers_];
    yIndex = new unsigned int[maxStickers_];
    this->background = new Image(background);
    stickers = new Image * [maxStickers_];
    for (unsigned temp = 0; temp < maxStickers_; temp++)
    {
      stickers[temp] = NULL;
    }
  }

  StickerSheet::~StickerSheet() {
    maxStickers_ = 0;
    stickerCount_ = 0;
    delete[] xIndex;
    xIndex = NULL;
    delete[] yIndex;
    yIndex = NULL;
    delete background;
    delete[] stickers;
    stickers = NULL;
  }

  StickerSheet::StickerSheet(const StickerSheet & other) {
    maxStickers_ = other.maxStickers_;
    stickerCount_ = other.stickerCount_;
    xIndex = new unsigned int[maxStickers_];
    yIndex = new unsigned int[maxStickers_];
    stickers = new Image * [maxStickers_];
    for (unsigned temp = 0; temp < maxStickers_ ; temp++) {
    if (other.stickers[temp] != NULL) {
      stickers[temp] = new Image(*(other.stickers[temp]));
      xIndex[temp] = other.xIndex[temp];
      yIndex[temp] = other.yIndex[temp];
    }
      background = new Image( * (other.background));
    }
  }

  void StickerSheet::changeMaxStickers(unsigned max) {
    if (maxStickers_ == max) {
      return;
    }
    unsigned * xIndexNew = new unsigned[max];
    unsigned * yIndexNew = new unsigned[max];
    Image * * stickersNew = new Image * [max];
    for (unsigned temp = 0; temp < max; temp++) {
      if(temp < stickerCount_) {
        xIndexNew[temp] = xIndex[temp];
        yIndexNew[temp] = yIndex[temp];
        stickersNew[temp] = new Image(*stickers[temp]);
      }
      else {
        xIndexNew[temp] = 0;
        yIndexNew[temp] = 0;
        stickersNew[temp] = NULL;
      }
    }
    delete [] xIndexNew;
    delete [] yIndexNew;
    for (unsigned temp = 0; temp < maxStickers_; temp++) {
      delete stickers[temp];
      stickers[temp] = NULL;
    }
    maxStickers_ = max;
    stickers = stickersNew;
  }

  int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
    unsigned ret = -1;
    if (stickerCount_ < maxStickers_) {
      for (unsigned temp = 0; temp < maxStickers_; temp++) {
        if (stickers[temp] == NULL) {
          stickerCount_++;
          xIndex[temp] = x;
          yIndex[temp] = y;
          stickers[temp] = new Image(sticker);
          ret = temp;
          break;
        }
      }
    }
    return ret;
  }

  bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (index < maxStickers_) {
      if (stickers[index] != NULL) {
        xIndex[index] = x;
        yIndex[index] = y;
        return true;
      }
    }
    return false;
  }

  void StickerSheet::removeSticker(unsigned index) {
    if (index < maxStickers_) {
      xIndex[index] = 0;
      yIndex[index] = 0;
      delete stickers[index];
      stickers[index] = NULL;
     	stickerCount_--;
    }
  }

  Image * StickerSheet::getSticker(unsigned index) const {
    if (index < maxStickers_) {
      return stickers[index];
    }
    return NULL;
  }

  const StickerSheet& StickerSheet::operator=(const StickerSheet & other) {
    if (&other != this) {
      StickerSheet::~StickerSheet();
      StickerSheet * ret = new StickerSheet(other);
      return *ret;
    }
    return *this;
  }

  Image StickerSheet::render() const{
    Image * pic = background;
    unsigned maxWidth = background->width();
    unsigned maxHeight = background->height();
    for (unsigned temp = 0; temp < maxStickers_; temp++) {
      if (stickers[temp] != NULL) {
        unsigned xMax = (*(xIndex + temp) + stickers[temp]->width());
        unsigned yMax = (*(yIndex + temp) + stickers[temp]->height());
        if (maxWidth < xMax) {
          maxWidth = xMax;
        }
        if (maxHeight < yMax) {
          maxHeight = yMax;
        }
      }
    }
    pic->resize(maxWidth, maxHeight);
    for (unsigned tempX = 0; tempX < pic->width(); tempX++) {
      for (unsigned tempY = 0; tempY < pic->height(); tempY++) {
          HSLAPixel & origPixel = background->getPixel(tempX,tempY);
          HSLAPixel & newPixel = pic->getPixel(tempX,tempY);
          newPixel = origPixel;
    }
  }
    for (unsigned temp = 0; temp < maxStickers_; temp++) {
      if (stickers[temp] != NULL) {
        for (unsigned x = 0; x < stickers[temp]->width(); x++) {
          for (unsigned y = 0; y < stickers[temp]->height(); y++) {
            HSLAPixel & origPixel = pic->getPixel(x + xIndex[temp], y + yIndex[temp]);
            HSLAPixel & newPixel = stickers[temp]->getPixel(x,y);
            if (newPixel.a != 0) {
              origPixel.h = newPixel.h;
              origPixel.s = newPixel.s;
              origPixel.l = newPixel.l;
              origPixel.a = newPixel.a;
            }
          }
        }
      }
    }
    return *pic;
}
}
