#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image picture;
  Image sticker1;
  Image sticker2;
  Image sticker3;
  picture.readFromFile("alma.png");

  sticker1.readFromFile("wolf.png");
  sticker2.readFromFile("moon.png");
  sticker3.readFromFile("stars.png");

  StickerSheet sheet(picture, 5);

  sheet.addSticker(sticker1, 250, 0);
  sheet.addSticker(sticker2, 300, 200);
  sheet.addSticker(sticker3, 300, 400);

  Image output = sheet.render();

  output.writeToFile("myImage.png");
  return 0;
}
