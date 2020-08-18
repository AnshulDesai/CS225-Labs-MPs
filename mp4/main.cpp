
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  PNG image;
  MyColorPicker mcp (.05);
  RainbowColorPicker rcp (.05);

  image.readFromFile("tests/pacman.png");

  FloodFilledImage flood (image);
  BFS bfs (image, Point(10, 25), 0.3);

  flood.addFloodFill(bfs, mcp);

  Animation animation = flood.animate(100);
  PNG preFrame = animation.getFrame( animation.frameCount() - 50 );

  FloodFilledImage flood2 (preFrame);
  DFS dfs (preFrame, Point(40, 5), 0.3);

  flood2.addFloodFill(dfs, rcp);

  Animation animation2 = flood2.animate(100);
  PNG lastFrame = animation2.getFrame(animation2.frameCount() - 1);

  lastFrame.writeToFile("myFloodFill.png");
  animation2.write("myFloodFill.gif");
  return 0;
}
