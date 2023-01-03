#include "Image.h"
#include "StickerSheet.h"

using namespace std;

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image tombak;       tombak.readFromFile("/workspaces/CS225/CS225-Fall2022/mp_stickers/tombak.png");
  Image setar;        setar.readFromFile("/workspaces/CS225/CS225-Fall2022/mp_stickers/setar.png");
  Image calligraphy;  calligraphy.readFromFile("/workspaces/CS225/CS225-Fall2022/mp_stickers/calligraphy.png");
  Image illum;        illum.readFromFile("/workspaces/CS225/CS225-Fall2022/mp_stickers/illum.png");

  calligraphy.scale(300, 300);
  calligraphy.illinify();
  setar.darken(0.2);
  illum.scale(300, 300);
  StickerSheet sheet(tombak, 5);
  sheet.addSticker(setar, 50, 50);
  sheet.addSticker(calligraphy, 1200, 500);
  sheet.addSticker(illum, 50, 550);
  Image rendered = sheet.render();
  rendered.writeToFile("../myImage.png");

  return 0;
}
