/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include <vector>
#include <set>
#include "Image.h"
#include "cs225/HSLAPixel.h"

using std::vector;

class StickerSheet {
public:
    StickerSheet(const Image& pic, unsigned max);
    StickerSheet(const StickerSheet& other);
    ~StickerSheet();

    void changeMaxStickers(unsigned max);
    int addSticker(Image& sticker, unsigned x, unsigned y);
    bool translate(unsigned index, unsigned x, unsigned y);
    void removeSticker(unsigned index);
    Image* getSticker(unsigned index);
    Image render() const;

    const StickerSheet& operator=(const StickerSheet& rhs);
    void Copy(const StickerSheet& other);
    void Clear();

private:
    struct Sticker {
        Image* image = nullptr;
        unsigned x = 0;
        unsigned y = 0;

        Sticker(): image(nullptr), x(0), y(0) {}

        Sticker(Image* im, unsigned xi, unsigned yi) {
            image = im;
            x = xi;
            y = yi;
        }
    };

    unsigned max_stickers_;
    int highest_layer_; // 0 indexed
    Image picture_;
    vector<Sticker> stickers_;
    // std::set<size_t> empty_indices_;

    void DrawSticker(Image& base_image, Sticker sticker) const;
    std::pair<unsigned, unsigned> GetImageDimWithStickers() const;
    bool FullStickers() const;
    bool IndexDeleted(unsigned index) const;
    bool InvalidIndex(unsigned index) const;
    void ShiftStickersElemDown(int start);
};