#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png):image_(png) {
  /** @todo [Part 2] */
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  operations_.push_back(make_pair(&traversal, &colorPicker));
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
  PNG image_animate = image_;
  Animation animation;
  animation.addFrame(image_animate);
  /** @todo [Part 2] */
  for (std::pair<ImageTraversal*, ColorPicker*> op : operations_) {
    ImageTraversal* traversal;
    ColorPicker* cp;
    std::tie(traversal, cp) = op;
    int count = 0;
    for (Point p : *traversal) {
      HSLAPixel& pixel = image_animate.getPixel(p.x, p.y);
      pixel = cp->getColor(p.x, p.y);
      ++count;
      if (count % frameInterval == 0) {
        animation.addFrame(image_animate);
      }
    }
    animation.addFrame(image_animate);
  }
  return animation;
}
