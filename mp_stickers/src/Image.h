/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once

#include <cmath>
#include <algorithm>
#include <vector>
#include <cassert>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using cs225::HSLAPixel;
using std::vector;

constexpr double illini_orange_hue = 11;
constexpr double illini_blue_hue = 216;

class Image : public cs225::PNG {
public:
    void darken(); // done
    void darken(double amount); // done
    void desaturate(); // done
    void desaturate(double amount); // done
    void grayscale(); // done
    void illinify(); // done
    void lighten(); // done
    void lighten(double amount); // done
    void rotateColor(double degrees);
    void saturate(); // done
    void saturate(double amount); // done
    void scale(double factor); // done
    void scale(unsigned w, unsigned h); // done (I think)

private:
    void ScaleDown(double factor);
    void ScaleUp(double factor);
    std::vector<std::vector<HSLAPixel>> CopyImageData();
};

/**
    Update pixel's luminance value according to amount.
    Clip resulting luminance to be in [0, 1]
*/
void ModifyPixelLuminance(HSLAPixel* pixel, double amount);
void ModifyPixelSaturation(HSLAPixel* pixel, double amount);
void ModifyPixelHue(HSLAPixel& pixel, double deg);