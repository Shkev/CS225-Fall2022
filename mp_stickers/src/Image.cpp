#include "Image.h"

void ModifyPixelLuminance(HSLAPixel& pixel, double amount) {
    pixel.l += amount;
    if (pixel.l < 0) pixel.l = 0;
    if (pixel.l > 1) pixel.l = 1; 
}

void ModifyPixelSaturation(HSLAPixel& pixel, double amount) {
    pixel.s += amount;
    if (pixel.s < 0) pixel.s = 0;
    if (pixel.s > 1) pixel.s = 1; 
}

void ModifyPixelHue(HSLAPixel& pixel, double deg) {
    pixel.h += deg;
    while (pixel.h >= 360) {
        pixel.h -= 360;
    }
    while (pixel.h < 0) {
        pixel.h += 360;
    }
}

void Image::darken(double amount) {
    for (size_t x = 0; x < width(); ++x) {
        for (size_t y = 0; y < height(); ++y) {
            HSLAPixel& pixel = getPixel(x, y);
            ModifyPixelLuminance(pixel, -1*amount);
        }
    }
}

void Image::darken() {
    darken(0.1);
}

void Image::lighten(double amount) {
    for (size_t x = 0; x < width(); ++x) {
        for (size_t y = 0; y < height(); ++y) {
            HSLAPixel& pixel = getPixel(x, y);
            ModifyPixelLuminance(pixel, amount);
        }
    }
}

void Image::lighten() {
    lighten(0.1);
}

void Image::desaturate(double amount) {
    for (size_t x = 0; x < width(); ++x) {
        for (size_t y = 0; y < height(); ++y) {
            HSLAPixel& pixel = getPixel(x, y);
            ModifyPixelSaturation(pixel, -1*amount);
        }
    }
}

void Image::desaturate() {
    desaturate(0.1);
}

void Image::saturate(double amount) {
    for (size_t x = 0; x < width(); ++x) {
        for (size_t y = 0; y < height(); ++y) {
            HSLAPixel& pixel = getPixel(x, y);
            ModifyPixelSaturation(pixel, amount);
        }
    }
}

void Image::saturate() {
    saturate(0.1);
}

void Image::grayscale() {
    for (size_t x = 0; x < width(); ++x) {
        for (size_t y = 0; y < height(); ++y) {
            HSLAPixel& pixel = getPixel(x, y);
            pixel.s = 0;
        }
    }
}

void Image::illinify() {
    for (size_t x = 0; x < width(); ++x) {
        for (size_t y = 0; y < height(); ++y) {
            HSLAPixel& pixel = getPixel(x, y);
            double orange_dist = fabs(pixel.h - illini_orange_hue);
            double blue_dist = fabs(pixel.h - illini_blue_hue);
            pixel.h = orange_dist < blue_dist ? illini_orange_hue : illini_blue_hue;
        }
    }
}

void Image::rotateColor(double degrees) {
    for (size_t x = 0; x < width(); ++x) {
        for (size_t y = 0; y < height(); ++y) {
            HSLAPixel& pixel = getPixel(x, y);
            ModifyPixelHue(pixel, degrees);
        }
    }
}

void Image::scale(double factor) {
    HSLAPixel* scaled_image;
    if (factor < 1) {
        ScaleDown(factor);
    } else {
        ScaleUp(factor);
    }
}

void Image::scale(unsigned w, unsigned h) {
    double factor = std::min(static_cast<double>(h)/height(), static_cast<double>(w)/width());
    scale(factor);
}

void Image::ScaleDown(double factor) {
    // factor < 1
    size_t new_factor = static_cast<size_t>(floor(1/factor));
    size_t original_width = width(), original_height = height();
    size_t scaled_width = ceil(original_width*factor), scaled_height = ceil(original_height*factor);

    vector<vector<HSLAPixel>> original_image = CopyImageData();
    size_t xloc = 0, yloc = 0; // indexing original image
    for (size_t y = 0; y < scaled_height; ++y, yloc+=new_factor) {
        for (size_t x = 0; x < scaled_width; ++x, xloc+=new_factor) {
            HSLAPixel& p = getPixel(x, y);
            p = original_image.at(yloc).at(xloc);
        }
        xloc = 0;
    }

    resize(scaled_width, scaled_height);
}

void Image::ScaleUp(double factor) {
    size_t new_factor = static_cast<size_t>(floor(factor));
    size_t original_width = width(), original_height = height();
    size_t scaled_width = original_width*new_factor, scaled_height = original_height*new_factor;

    vector<vector<HSLAPixel>> original_image = CopyImageData();
    resize(scaled_width, scaled_height);

    size_t xloc = 0, yloc = 0; // indexing original image
    size_t xcnt = 0, ycnt = 0;
    for (size_t y = 0; y < height(); ++y) {
        for (size_t x = 0; x < width(); ++x) {
            HSLAPixel& p = getPixel(x, y);
            p = original_image.at(yloc).at(xloc);
            xcnt++;
            if (xcnt == new_factor) {
                xcnt = 0;
                xloc++;
            }
            if (xloc == original_width) {
                xloc = 0;
            }
        }
        assert(xloc == 0);
        ycnt++;
        if (ycnt == new_factor) {
            ycnt = 0;
            yloc++;
        }
    }
}

void CopyRowNTimes(HSLAPixel* image, std::pair<size_t, size_t> row_start_info, size_t ncopy) {
    size_t row_start, row_length;
    std::tie(row_start, row_length) = row_start_info;
    for (size_t c = 1; c <= ncopy; ++c) {
        size_t copy_start = row_start + c*row_length;
        for (size_t loc = 0; loc < row_length; ++loc) {
            image[copy_start+loc] = image[row_start+loc];
        }
    }
}

vector<vector<HSLAPixel>> Image::CopyImageData() {
    vector<vector<HSLAPixel>> image_copy(height(), vector<HSLAPixel>(width()));
    for (size_t x = 0; x < width(); ++x) {
        for (size_t y = 0; y < height(); ++y) {
            image_copy.at(y).at(x) = getPixel(x, y);
        }
    }
    return image_copy;
}