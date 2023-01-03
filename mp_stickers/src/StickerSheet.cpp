#include "StickerSheet.h"

using std::cout;

StickerSheet::StickerSheet(const Image& pic, unsigned max): max_stickers_(max), highest_layer_(-1) {
    picture_ = pic;
    stickers_ = vector<Sticker>(max);
}

StickerSheet::StickerSheet(const StickerSheet& other) {
    Copy(other);
}

StickerSheet::~StickerSheet() {
    Clear();
}

const StickerSheet& StickerSheet::operator=(const StickerSheet& rhs) {
    if (this == &rhs) return *this;
    Clear();
    Copy(rhs);
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max) {
    stickers_.resize(max);
    max_stickers_ = max;
    if (static_cast<int>(max) <= highest_layer_) {
        highest_layer_ = max-1;
    }
}

int StickerSheet::addSticker(Image& sticker, unsigned x, unsigned y) {
    Sticker new_sticker = Sticker(&sticker, x, y);
    if (FullStickers()) return -1;
    stickers_.at(++highest_layer_) = new_sticker;
    return highest_layer_;
    // if (empty_indices_.empty()) {
    //     stickers_.at(++highest_layer_) = new_sticker;
    //     return highest_layer_;
    // } else { // if there are open spots earlier in array
    //     size_t index = *empty_indices_.begin(); // get first available empty index
    //     stickers_.at(index) = new_sticker;
    //     return index;
    // }
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (InvalidIndex(index)) {
        return false;
    }
    Sticker& s = stickers_.at(index);
    s.x = x;
    s.y = y;
    return true;
}

void StickerSheet::removeSticker(unsigned index) {
    // empty_indices_.insert(index);
    if (static_cast<int>(index) > highest_layer_) return;
    // if (static_cast<int>(index) == highest_layer_) highest_layer_--;
    ShiftStickersElemDown(index+1);
    highest_layer_--;
}

Image* StickerSheet::getSticker(unsigned index) {
    if (InvalidIndex(index)) {
        return nullptr;
    }
    return stickers_.at(index).image;
}

Image StickerSheet::render() const {
    Image rendered_image = picture_;
    unsigned new_width, new_height;
    std::tie(new_width, new_height) = GetImageDimWithStickers();
    assert(new_height >= picture_.height());
    assert(new_width >= picture_.width());
    rendered_image.resize(new_width, new_height);
    // Note: Stickers can extend the base picture to the right or bottom
    // (not top or left bc x, y of top left of each sticker is >= 0).
    for (size_t i = 0; (int)i <= highest_layer_; ++i) {
        // if (IndexDeleted(i)) continue;
        Sticker sticker = stickers_.at(i);
        DrawSticker(rendered_image, sticker);
    }
    return rendered_image;
}

void StickerSheet::Copy(const StickerSheet& other) {
    picture_ = other.picture_;
    max_stickers_ = other.max_stickers_;
    highest_layer_ = other.highest_layer_;
    // empty_indices_ = other.empty_indices_;
    stickers_ = other.stickers_;
}

void StickerSheet::Clear() {
    // nothing to do
}

bool StickerSheet::FullStickers() const {
    return (highest_layer_ == static_cast<int>(max_stickers_)) /* &&  (empty_indices_.empty()) */;
}

// bool StickerSheet::IndexDeleted(unsigned index) const {
//     return empty_indices_.count(index) > 0;
// }

bool StickerSheet::InvalidIndex(unsigned index) const {
    return (static_cast<int>(index) > highest_layer_) /* || IndexDeleted(index) */;
}

void StickerSheet::DrawSticker(Image& base_image, Sticker sticker) const {
    for (size_t y = 0; y < sticker.image->height(); ++y) {
        for (size_t x = 0; x < sticker.image->width(); ++x) {
            assert(x+sticker.x < base_image.width());
            assert(y+sticker.y < base_image.height());
            HSLAPixel& sticker_pixel = sticker.image->getPixel(x, y);
            if (sticker_pixel.a == 0) continue;
            HSLAPixel& pixel_to_change = base_image.getPixel(x+sticker.x, y+sticker.y);
            pixel_to_change = sticker_pixel;
        }
    }
}

std::pair<unsigned, unsigned> StickerSheet::GetImageDimWithStickers() const {
    unsigned new_height = picture_.height(), new_width = picture_.width();
    for (size_t i = 0; (int)i <= highest_layer_; ++i) {
        Sticker s = stickers_.at(i);
        // if (IndexDeleted(i)) continue;
        new_width = std::max(new_width, s.x+s.image->width());
        new_height = std::max(new_height, s.y+s.image->height());
    }
    return std::make_pair(new_width, new_height);
}

void StickerSheet::ShiftStickersElemDown(int start) {
    if (start > highest_layer_) return;
    for (int i = start; i <= highest_layer_; ++i) {
        stickers_.at(i-1) = stickers_.at(i);
    }
}