
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
  PNG png;       
  png.readFromFile("monarch.png");
  FloodFilledImage image(png);
  BFS bfs(png, Point(222, 122), 0.2);
  DFS dfs(png, Point(162, 194), 0.2);
  DFS dfs1(png, Point(153, 87), 0.2);
  MyColorPicker mycolor;
  RainbowColorPicker rainbow(0.05);

  image.addFloodFill( dfs, mycolor );
  image.addFloodFill( bfs, rainbow );
  image.addFloodFill( dfs1, mycolor );
  
  Animation animation = image.animate(500);

  
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  


  return 0;
}
