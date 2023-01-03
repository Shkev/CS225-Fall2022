
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cstddef>
#include <cassert>

template <class T, class Compare>
class heap;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return currentIdx*2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return currentIdx*2 + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return currentIdx / 2; // floor division
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    return _elems.size() > leftChild(currentIdx);
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    size_t lchild = leftChild(currentIdx), rchild = rightChild(currentIdx);
    if (lchild >= _elems.size()) return rchild; // has no left child. must have right child
    if (rchild >= _elems.size()) return lchild;
    return higherPriority(_elems.at(lchild), _elems.at(rchild)) ? lchild : rchild;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    assert(currentIdx > 0);
    // @TODO Implement the heapifyDown algorithm.
    if (!hasAChild(currentIdx)) return;
    size_t min_child_idx = maxPriorityChild(currentIdx);
    if (higherPriority(_elems.at(min_child_idx), _elems.at(currentIdx))) {
        std::swap(_elems.at(currentIdx), _elems.at(min_child_idx));
        heapifyDown(min_child_idx);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    assert(currentIdx > 0);
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying

    // 1-indexing vector
    // index 0 stores number of elements in heap
    _elems.push_back(T());
    assert(_elems.size() == 1);
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems.push_back(T());
    _elems.insert(_elems.end(), elems.begin(), elems.end());
    assert(_elems.size() == elems.size()+1);
    for (size_t i = _elems.size()-1; i > 0; --i) {
        heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    if (_elems.size() == 1) return T();
    T rem_elem = _elems.at(root());
    std::swap(_elems.at(root()), _elems.back());
    _elems.pop_back();
    heapifyDown(root());
    return rem_elem;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return root();
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    T prev = _elems.at(idx);
    _elems.at(idx) = elem;
    if (higherPriority(elem, prev)) {
        heapifyUp(idx);
    } else {
        heapifyDown(idx);
    }
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return _elems.size() == 1;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
