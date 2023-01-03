/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List(): head_(NULL), tail_(NULL), length_(0) { 
  // @TODO: graded in MP3.1
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_, &tail_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL, &tail_);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  while (head_ != NULL) {
    ListNode* next = head_->next;
    delete head_;
    head_ = next;
  }
  tail_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode* newNode = new ListNode(ndata);
  newNode->next = head_;
  newNode->prev = NULL;
  
  if (head_ != NULL) {
    head_->prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  head_ = newNode;
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode* new_node = new ListNode(ndata);
  new_node->next = NULL;
  new_node->prev = tail_;

  if (tail_ != NULL) {
    tail_->next = new_node;
  }
  if (head_ == NULL) {
    head_ = new_node;
  }
  tail_ = new_node;
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode* curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) { // new list head is curr
      // detach end of first list from curr
      if (curr->prev != NULL) {
        curr->prev->next = NULL;
      }
      tail_ = curr->prev;
      curr->prev = NULL;
      
      return curr;
  }

  return NULL;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  int i = 0;
  ListNode* curr = head_;
  ListNode* tmp1 = NULL;
  ListNode* tmp2 = NULL;
  while (curr != NULL) {
    stringstream s;
    if (i == 0) {
      tmp1 = curr;
    } else if (i == 1) {
      tmp2 = curr;
    } else if (i == 2) {
      SwapListNodes(tmp1, curr);
      SwapListNodes(curr, tmp2);
      i = -1;
      curr = tmp1;
    }
    curr = curr->next;
    ++i;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  ListNode* curr = endPoint;
  ListNode* one_before_start = startPoint->prev;
  while (curr != one_before_start) {
    std::swap(curr->next, curr->prev);
    curr = curr->next;
  }
  std::swap(startPoint, endPoint);

  // fixing links in the list after reversal
  std::swap(endPoint->next, startPoint->prev);
  if (endPoint->next != NULL)
      endPoint->next->prev = endPoint;
  if (startPoint->prev != NULL)
    startPoint->prev->next = startPoint;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  ListNode* start = head_;
  ListNode* end = start;
  while (end != NULL) {
    for (int i = 0; i < n-1 && end->next != NULL; ++i) {
      end = end->next;
    }
    assert(end != NULL);
    reverse(start, end);
    if (end == head_) {
      head_ = start;
    }

    start = end->next;
    end = start;
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
  /// @todo Graded in MP3.2

  ListNode* curr = NULL;
  if (first == NULL) {
    return second;
  }
  if (second == NULL) {
    return first;
  }

  if (first->data < second->data) {
    curr = first;
    first = first->next;
  } else {
    curr = second;
    second = second->next;
  }
  ListNode* merged_head = curr;
  while (first != NULL && second != NULL) {
    if (first->data < second->data) {
      curr->next = first;
      curr->next->prev = curr;
      curr = curr->next;
      first = first->next;
    } else {
      curr->next = second;
      curr->next->prev = curr;
      curr = curr->next;
      second = second->next;
    }
  }
  if (first == NULL) { // first reached end of list before second
    curr->next = second;
  } else if (second == NULL) {
    curr->next = first;
  }
  return merged_head;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (start == NULL) {
    assert(chainLength == 0);
    return NULL;
  }
  if (start->next == NULL) {
    assert(chainLength == 1);
    return start;
  }
  int mid = chainLength / 2;
  ListNode* left_sublist = start;
  ListNode* right_sublist = start;

  // get head of right sublist
  for (int i = 0; i < mid; ++i) {
    right_sublist = right_sublist->next;
  }

  right_sublist->prev->next = NULL; // separating two sublists
  right_sublist->prev = NULL;
  ListNode* merged_list = merge(mergesort(left_sublist, mid), mergesort(right_sublist, chainLength-mid));
  
  return merged_list;
}

template <typename T>
void List<T>::SwapListNodes(ListNode* a, ListNode* b) {
  // a must come before b in list
  ListNode* tmp = b->prev;

  if (a->prev != NULL) {
    a->prev->next = b;
  }
  if (b->next != NULL) {
    b->next->prev = a;
  }
  b->prev->next = a;
  b->prev = a->prev;
  a->prev = tmp;
  a->next->prev = b;
  tmp = a->next;
  a->next = b->next;
  b->next = tmp;

  if (head_ == a) {
    head_ = b;
  }
  if (tail_ == b) {
    tail_ = a;
  }
}
