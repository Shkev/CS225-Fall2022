#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using std::cout;

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator():
traversal_(nullptr), current_(Point()) {
  /** @todo [Part 1] */
}

ImageTraversal::Iterator::Iterator(ImageTraversal* traversal): traversal_(traversal) {
  current_ = traversal_->peek();
  if (traversal_ != nullptr)
    traversal_->visited_ = std::vector<std::vector<bool>>(
      traversal_->search_space_.height(),
      std::vector<bool>(traversal_->search_space_.width(), false));
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator& ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  traversal_->visited_.at(current_.y).at(current_.x) = true;
  if (!traversal_->empty()) {
    current_ = traversal_->pop();
    AddPointNeighbors(current_);
    RemoveNextVisitedPoints();
    try {
      current_ = traversal_->peek();
    } catch (const std::runtime_error& e) { // empty traversal_
      traversal_ = nullptr;
      current_ = Point();
      return *this;
    }
  }

  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */

  bool this_empty = false, other_empty = false;
  if (traversal_ == nullptr) this_empty = true;
  if (other.traversal_ == nullptr) other_empty = true;

  if (!this_empty) this_empty = traversal_->empty();
  if (!other_empty) other_empty = other.traversal_->empty();

  if (this_empty && other_empty) return false;
  else if (!this_empty && !other_empty) return traversal_ != other.traversal_;

  return true;
}

// Private Helper functions

bool ImageTraversal::Iterator::Visited(const Point& p) {
  return traversal_->visited_.at(p.y).at(p.x);
}

bool ImageTraversal::Iterator::IsNotValidPoint(const Point& p, double delta) {
  return Visited(p) || (delta >= traversal_->tolerance_);
}

bool ImageTraversal::Iterator::WithinSearchSpace(const Point& p) {
  const PNG& ss = traversal_->search_space_;
  return p.x < ss.width() && p.x >= 0 && p.y < ss.height() && p.y >= 0;
}

void ImageTraversal::Iterator::AddPointNeighbors(const Point& p) {
  const PNG& ss = traversal_->search_space_;
  const HSLAPixel& start_pixel = ss.getPixel(traversal_->start_.x, traversal_->start_.y);
  const std::vector<Point> neighbors = {Point(p.x+1, p.y), Point(p.x, p.y+1), Point(p.x-1, p.y), Point(p.x, p.y-1)};

  for (Point neighbor : neighbors) {
    if (WithinSearchSpace(neighbor)) {
      const HSLAPixel& neighbor_pixel = ss.getPixel(neighbor.x, neighbor.y);
      double delta = calculateDelta(start_pixel, neighbor_pixel);
      if (!IsNotValidPoint(neighbor, delta)) {
        traversal_->add(neighbor);
      }
    }
  }
}

void ImageTraversal::Iterator::RemoveNextVisitedPoints() {
  while (!traversal_->empty() && Visited(traversal_->peek())) {
    traversal_->pop();
  }
}