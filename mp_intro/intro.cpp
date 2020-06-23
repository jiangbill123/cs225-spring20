#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  PNG* input = new PNG();
  //std::cout << "Reached line " << __LINE__ << std::endl;
  input->readFromFile(inputFile);
   int width = input->width();
   int height = input->height();
  PNG* output = new PNG(width, height);
  for(int x = 0; x < width; x++){
    for(int y = 0; y < height; y++){
      HSLAPixel & pixel1 = input->getPixel(x, y);
      HSLAPixel & pixel2 = output->getPixel(width - x - 1, height - y - 1);
      pixel2 = pixel1;
    }
  }
  output->writeToFile(outputFile);
  delete output;
  delete input;
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  for(unsigned int x = 0; x < width; x++){
    for(unsigned int y = 0; y < height; y++){
      HSLAPixel & pixel = png.getPixel(x, y);
      pixel.h = (double(x)/double(width))*272 + 22;
      pixel.s = 0.55 + (double(y)/double(height))*0.45;
      pixel.l = 0.5;
      if (y<(height/2)){
        pixel.l = 0.5 + ((double(height/2)-double(y))/double(height/2))*0.3;
      }
      if (y>=(height/2)){
        pixel.l = 0.5 + ((double(y)-double(height/2))/double(height/2))*0.3;
      }
      pixel.a = 1;
    }
  }

  return png;
}
