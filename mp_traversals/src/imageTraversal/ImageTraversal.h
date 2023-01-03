/**
 * @file ImageTraversal.h
 */
#pragma once

#include <iterator>
#include <set>
#include <vector>
#include <stdexcept>
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "../Point.h"

using namespace cs225;

/**
 * A base class for traversal algorithms on images.
 *
 * BFS and DFS will inherit from this class
 * 
 * Each derived class must maintain an ordering of points on an image,
 * through calls to the virtual member functions `add` and `pop`.
 * 
 * A derived class provides a traversal by returning instances of
 * ImageTraversal::Iterator.
 */
class ImageTraversal {
public:

  ImageTraversal() = default;

  /**
   * A forward iterator through an ImageTraversal.
   */
  class Iterator : std::iterator<std::forward_iterator_tag, Point> {
  public:
    Iterator();
    Iterator(ImageTraversal* traversal);

    Iterator& operator++();
    Point operator*();
    bool operator!=(const Iterator &other);

    /** @todo [Part 1] */
    /** add member functions if neccesary*/

  private:
    /** @todo [Part 1] */
    ImageTraversal* traversal_;
    Point current_;

    bool Visited(const Point& p);

    /**
     * Returns true if the point is within tolerance of 
     * traversal_'s start and if it's unvisited.
     */
    bool IsNotValidPoint(const Point& p, double delta);
    bool WithinSearchSpace(const Point& p);

    /**
     * Adds all nonvisited neighbors points of p
     * that are within the tolerance to traversal_
    */
    void AddPointNeighbors(const Point& p);

    void RemoveNextVisitedPoints();
  };

  /**
   * The begining of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator begin() = 0;

  /**
   * The end of an iterator
   * Virtual function. Derived class need to implement this
   */
  virtual Iterator end() = 0;

  /**
   * Add new point to the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual void add(const Point & t) = 0;
  /**
   * Remove and return the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Point pop() = 0;
  /**
   * Return but not remove the next point of the traversal
   * Virtual function. Derived class need to implement this
   */
  virtual Point peek() const = 0;
  /**
   * To see if the traversal has no points left
   * Virtual function. Derived class need to implement this
   */
  virtual bool empty() const = 0;

protected:
  PNG search_space_;
  Point start_;
  double tolerance_;

private:
  std::vector<std::vector<bool>> visited_;

  static double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2);
};
