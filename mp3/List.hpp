/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */


/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(tail_->next);
}

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <typename T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  _destroy();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  while (head_ != nullptr) { // Iterates through each node of the list
    tail_ = head_->next; // Sets the tail to the next pointer of the head
    delete head_; // Deletes the head
    head_ = tail_; // Sets the head to the tail
  }
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
  ListNode * element = new ListNode(ndata); // Creates temporary data based off of the data in the parameter
  if (head_ != NULL) { // If there is data in the list
    length_++; // Incremenets the length of the list
    element->next = head_; // Sets the next pointer of the newly created node to the head of the list
    head_->prev = element; // Sets the previous pointer of the head of the list to the newly created node
    head_ = element; // Makes sure the head is now the element
    element = NULL; // Clears element
    // std::cout << "Line 66" << std::endl;
  }
  else { // If there is no data in the list
    length_++; // Increments the length of the list
    tail_ = element; // Sets the tail of the list to the element
    head_ = element; // Sets the head of the list to the element
    // std::cout << "Line 72" << std::endl;
  }
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
  ListNode * element = new ListNode(ndata); // Creates temporary data based off of the data in the parameter
  if (tail_ != NULL) { // If there is data in the list
    length_++; // Increments the length of the list
    tail_->next = element; // Sets the next pointer of the tail to the element
    element->prev = tail_; // Sets the prev pointer of the element to the tail
    tail_ = element; // Makes sure the tail is now the element
    element = NULL; // Clears element
    // std::cout << "Line 92" << std::endl;
  }
  else { // If there is no data in the list
    length_++; // Incremenets the length of the list
    tail_ = element; // Sets the tail of the list to the element
    head_ = element; // Sets the head of the list to the element
    // std::cout << "Line 98" << std::endl;
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_); // Reverses whole list, from head to tail
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
  /// @todo Graded in MP3.1
  bool endCheck = (startPoint == NULL || endPoint == NULL); // Creates boolean that checks if startPoint or endPoint are NULL
  if (endCheck) {
    return; // If either or NULL, return
  }

  ListNode * tempStart = startPoint; // Creates pointer to startPoint
  ListNode * tempPrev = startPoint; // Creates pointer to startPoint (Adjusts prev)
  ListNode * tempNode; // Creates tempNode
  while (tempPrev != NULL) { // Iterates through tempPrev
    tempNode = tempPrev->prev; // Sets tempNode to prev of tempPrev
    tempPrev->prev = tempPrev->next; // Sets tempPrev->prev value to tempPrev->next
    // std::cout << "Line 135" << std::endl;
    tempPrev->next = tempNode; // Sets tempPrev->next to tempNode
    tempPrev = tempPrev->prev; // Sets tempPrev to tempPrev->prev (for iteration)
    // std::cout << "Line 138" << std::endl;
  }
  if (tempNode != NULL) {
    startPoint = tempNode->prev;  // Start point is set to tempNode->prev if tempNode is not NULL
    // std::cout << "Line 142" << std::endl;
  }

  endPoint = tempStart; // Sets endPoint to adjusted tempStart
}

 /**
  * Reverses blocks of size n in the current List. You should use your
  * reverse( ListNode * &, ListNode * & ) helper function in this method!
  *
  * @param n The size of the blocks in the List to be reversed.
  */
 template <class T>
 void List<T>::reverseNth( int n )
 {
   /// @todo Graded in MP3.1

 }

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  ListNode * curr = head_; // Creates temporary current pointer to the head
  if(head_ == tail_ || head_->next == NULL) { // If the head is the tail or if the next value of the head is NULL, returns
    return;
  }

  for (int count = 1; count < length_; count++) { // Iterates through the length of the list
    if (count % 2 == 0) { // If every other node
      insertBack(curr->data); // Inserts data to the back of the list
      ListNode * tempNode = curr->next; // Creates a temp node and sets the next pointer of curr
      curr->prev->next = tempNode; // Sets the next pointer of prev to the tempNode
      tempNode->prev = curr->prev; // Sets prev pointer of tempNode to the prev pointer of curr
    }
    curr = curr->next; // Iterates to next curr
  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <typename T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
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
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  if (splitPoint == 0) { // If splitPoint = 0, returns start
    return start;
  }
  if (splitPoint > length_) { // If splitPoint is greater than the length of the list, returns start
    return start;
  }
  if (start == NULL) { // If start is NULL, returns NULL
    return NULL;
  }

  ListNode * tempNode = start; // Creates temporary pointer to start
  int count = 0; // Creates count
  while (count < splitPoint) { // If count < splitPoint
    tempNode = tempNode->next; // Iterates to next tempNode
    count++; // Increments count
  }
  tempNode->prev->next = NULL; // Sets next pointer of prev to NULL
  tempNode->prev = NULL; // Sets prev pointer to NULL

  return tempNode; // returns tempNode
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
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second) {
  /// @todo Graded in MP3.2
  if (first == second) { // If first and second are the same nodes, return first
    return first;
  }
  if (first == NULL) { // If first is NULL, return second
    return second;
  }
  if (second == NULL) { // If second is NULL, return first
    return first;
  }

  // Creates temporary pointers which will be used to compare
  ListNode * tempMerge = NULL; // Merged list
  ListNode * tempCheck = NULL; // Temp node used for assigning
  ListNode * tempFirst = first; // Temporary pointer to first ListNode
  ListNode * tempSecond = second; // Temporary pointer to second ListNode

  // Compares the first data value for each node
  if (tempFirst->data < tempSecond->data ) { // If first < second
    tempMerge = tempFirst;
    head_ = tempFirst->next; // Sets head to first node
    tempFirst = tempFirst->next;
  }
  else { // If second < first
    tempMerge = tempSecond;
    head_ = tempSecond->next; // Sets head to second node
    tempSecond = tempSecond->next;
  }

  while (tempFirst != NULL || tempSecond != NULL ) { // Iterates through each list
    bool dataTest = (tempFirst != NULL && tempFirst->data < tempSecond->data); // Test that will be used later
    if (tempSecond == NULL || dataTest) { // Test for boolean OR if second list has reached the end
      tempMerge->next = tempFirst; // Sets next value of merged to iterated tempFirst
      tempMerge->next->prev = tempMerge; // Ensures the next value's prev pointer points to iterated tempMerge
      tempCheck = tempMerge->next; // Adjusts the next value
      tempFirst = tempFirst->next; // Iterates to the next value from the firstList
      tempMerge = tempMerge->next; // Iterates to the next value of the merged list
    }
    else {
      tempMerge->next = tempSecond; // Sets next value of merged to iterated tempSecond
      tempMerge->next->prev = tempMerge; // Ensures the next value's prev pointer points to iterated tempMerge
      tempCheck = tempMerge->next; // Adjusts the next value
      tempSecond = tempSecond->next; // Iterates to the next value from the secondList
      tempMerge = tempMerge->next; // Iterates the next value of the merged list
    }
  }

  if (first->data < second->data) { // Compares data to return first or second node
    return first;
  }
  return second;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <typename T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(chainLength < 2) { // Returns start if chainLength is less than 2
    return start;
  }
  int temp = chainLength / 2; // Creates an int with half the chainLength
  ListNode * first = start; // Creates pointer to start
  ListNode * second = split(first, temp); // Creates pointer which splits first by temp
  return merge(mergesort(first, temp), mergesort(second, chainLength - temp)); // Merge sort
}
