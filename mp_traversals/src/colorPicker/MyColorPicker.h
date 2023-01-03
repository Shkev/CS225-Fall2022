#pragma once

#include "ColorPicker.h"
#include "cs225/HSLAPixel.h"
#include "../Point.h"

using namespace cs225;

const HSLAPixel kBlackPixel = HSLAPixel(0, 0, 0);
const HSLAPixel kWhitePixel = HSLAPixel(0, 1, 1);

/**
 * A color picker class using your own color picking algorithm
 * 
 * Creates black and white colors
 */
class MyColorPicker : public ColorPicker {
public:
  HSLAPixel getColor(unsigned x, unsigned y);

private:

};
