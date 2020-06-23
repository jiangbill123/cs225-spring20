#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma, sticker, dab, shock, output;
  alma.readFromFile("alma.png");
  sticker.readFromFile("sticker.png");
  dab.readFromFile("dab.png");
  shock.readFromFile("shock.png");

  StickerSheet myimage(alma, 3);
  myimage.addSticker(sticker, 480, 10);
  myimage.addSticker(dab, 200, 350);
  myimage.addSticker(shock, 530, 120);
  output = myimage.render();
  output.writeToFile("myImage.png");

  return 0;
}
