class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    // @TODO: graded in MP3.1
    ListNode* position_;
    ListNode* const* list_tail;

  public:
    ListIterator() : position_(NULL) { }
    ListIterator(ListNode* x, ListNode* const* tail) : position_(x), list_tail(tail) { }


    // Pre-Increment, ++iter
    ListIterator& operator++() {
        // @TODO: graded in MP3.1
        if (position_ == NULL) return *this; // do not change position_
        position_ = position_->next;
        return *this;
    }
    
    // Post-Increment, iter++
    ListIterator operator++(int) {
        // @TODO: graded in MP3.1
        ListNode* temp = position_;
        operator++();
        return ListIterator(temp, list_tail);
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        // @TODO: graded in MP3.1
        if (position_ == NULL) { // position is past end
            position_ = *list_tail;
        } else {
            position_ = position_->prev;
        }
        return *this;
    }

    // Post-Decrement, iter--
    ListIterator operator--(int) {
        ListNode* temp = position_;
        operator--();
        return ListIterator(temp, list_tail);
    }

    bool operator!=(const ListIterator& rhs) {
        // @TODO: graded in MP3.1
        return position_ != rhs.position_;
    }

    bool operator==(const ListIterator& rhs) {
        return !(*this != rhs);
    }

    const T& operator*() {
        // if (position_ == NULL) {
        //     return T();
        // }
        return position_->data;
    }

    const T* operator->() {
        if (position_ == NULL) {
            return NULL;
        }
        return &(position_->data);
    }
};
