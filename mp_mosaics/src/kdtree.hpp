/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <tuple>
#include <cassert>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
  /**
   * @todo Implement this function!
   */
  if (first[curDim] == second[curDim]) return first < second;
  return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
  /**
   * @todo Implement this function!
   */
  long curr_dist = PointDistSquared<Dim>(target, currentBest);
  long potential_dist = PointDistSquared<Dim>(target, potential);
  if (curr_dist == potential_dist) {
    return potential < currentBest;
  }
  return potential_dist < curr_dist;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints): size(newPoints.size())
{
  /**
   * @todo Implement this function!
   */
  vector<Point<Dim>> points = newPoints;
  BuildTree(root, points, {0, newPoints.size()-1, 0});
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  Copy(other);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (&rhs == this) return *this;
  Clear(root);
  Copy(rhs);
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  Clear(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
  /**
   * @todo Implement this function!
   */
  return FindNearestNeighbor(root, query, 0);
}

template <int Dim>
void KDTree<Dim>::Clear(KDTreeNode* subroot) {
  if (subroot) {
    Clear(subroot->left);
    Clear(subroot->right);
    delete subroot;
  }
}

template <int Dim>
void KDTree<Dim>::Copy(const KDTree& other) {
  size = other.size;
  root = CopyTree(other.root);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::CopyTree(KDTreeNode* other_subroot) {
  if (!other_subroot) return;
  KDTreeNode* copied_subroot = new KDTreeNode(other_subroot->point);
  copied_subroot->left = CopyTree(other_subroot->left);
  copied_subroot->right = CopyTree(other_subroot->right);
  return copied_subroot;
}

template <int Dim>
void KDTree<Dim>::BuildTree(KDTreeNode*& subroot, vector<Point<Dim>>& new_points, tuple<int, int, int> points_info) {
  int start, end, dim;
  tie(start, end, dim) = points_info;

  if (end < start || end < 0 || start < 0 || end >= (int)new_points.size() || start >= (int)new_points.size()) return;

  assert(end < (int)new_points.size()); // end must be an index we can access in the tree

  size_t median_index = (start+end)/2; // floor division
  Point<Dim> median = QuickSelect<Dim>(new_points, median_index, {start, end, dim});
  subroot = new KDTreeNode(median);

  BuildTree(subroot->left, new_points, {start, median_index-1, (dim+1) % Dim});
  BuildTree(subroot->right, new_points, {median_index+1, end, (dim+1) % Dim});
}

template <int Dim>
Point<Dim> KDTree<Dim>::FindNearestNeighbor(KDTreeNode* curr, const Point<Dim>& target, int depth) const {
  assert(curr != nullptr);
  KDTreeNode* next_child = nullptr;
  KDTreeNode* other_child = nullptr;
  int dim = depth % Dim;
  if (smallerDimVal(target, curr->point, dim)) {
    next_child = curr->left;
    other_child = curr->right;
  } else {
    next_child = curr->right;
    other_child = curr->left;
  }

  Point<Dim> child_res, best = curr->point;
  if (next_child != nullptr) {
    child_res = FindNearestNeighbor(next_child, target, depth+1);
    best = ClosestPoint(target, child_res, curr->point);
  }

  long radius_squared = PointDistSquared(target, best);
  long dist = target[dim] - curr->point[dim];
  if (dist * dist <= radius_squared) {
    if (other_child != nullptr) {
      child_res = FindNearestNeighbor(other_child, target, depth+1);
      best = ClosestPoint(target, best, child_res);
    } // otherwise best doesn't change
  }

  return best;
}

template <int Dim>
Point<Dim> KDTree<Dim>::ClosestPoint(const Point<Dim>& target, const Point<Dim>& a, const Point<Dim>& b) const {
  if (shouldReplace(target, a, b)) {
    return b;
  }
  return a;
}

// non-member helper functions

template <int Dim>
long PointDistSquared(Point<Dim> a, Point<Dim> b) {
  long dist = 0;
  for (size_t i = 0; i < Dim; ++i) {
    dist += (a[i] - b[i])*(a[i] - b[i]);
  }
  return dist;
}

template <int Dim>
Point<Dim> QuickSelect(vector<Point<Dim>>& points, size_t k, tuple<int, int, int> points_info) {
  int start, end, dim;
  tie(start, end, dim) = points_info;
  size_t p = start;
  Point<Dim>& pivot = points.at(end);

  KDTree<Dim> kdt; // stupid workaround
  for (int i = start; i < end; ++i) { // last elem is the pivot, don't visit it
    if (kdt.smallerDimVal(points.at(i), pivot, dim)) {
      swap(points.at(i), points.at(p));
      p++;
    }
  }
  swap(pivot, points.at(p));
  if (k > p) {
    return QuickSelect(points, k, {p+1, end, dim});
  }
  if (k < p) {
    return QuickSelect(points, k, {start, p-1, dim});
  }
  return points.at(p);
}
