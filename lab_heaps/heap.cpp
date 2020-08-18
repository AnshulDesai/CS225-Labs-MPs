
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return (2 * currentIdx + 1);
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return (2 * currentIdx + 2);
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    if (currentIdx % 2 == 0) {
      return (currentIdx - 2) / 2;
    }
    return (currentIdx - 1) / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    return (leftChild(currentIdx) < _elems.size());
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    if (hasAChild(currentIdx)) {
      if (rightChild(currentIdx) >= _elems.size()) {
        return leftChild(currentIdx);

      }
      else if (higherPriority(_elems[rightChild(currentIdx)], _elems[leftChild(currentIdx)])) {
          return rightChild(currentIdx);
      }
      else {
          return leftChild(currentIdx);
      }
    }
    return -1;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    int pcIndex = maxPriorityChild(currentIdx);
    if (pcIndex < 0) {
      return;
    }
    if (higherPriority(_elems[maxPriorityChild(currentIdx)], _elems[currentIdx])) {
      T temp = _elems[pcIndex];
      _elems[pcIndex] = _elems[currentIdx];
      _elems[currentIdx] = temp;
      heapifyDown(pcIndex);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    size_t parentIdx = parent(currentIdx);
    if(currentIdx == root()) {
      return;
    }
    if(higherPriority(_elems[currentIdx], _elems[parentIdx])) {
      T temp = _elems[parentIdx];
      _elems[parentIdx] = _elems[currentIdx];
      _elems[currentIdx] = temp;
      heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems = elems;
    for (size_t i = parent(_elems.size()); i > 0; i--) {
      heapifyDown(i);
    }
    heapifyDown(root());
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    if (empty()) {
      return T();
    }
    T temp = _elems[root()];
    T tempSwap = _elems[root()];
    _elems[root()] = _elems[_elems.size() - 1];
    _elems[_elems.size() - 1] = tempSwap;
    _elems.pop_back();
    heapifyDown(root());
    return temp;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    if (empty()) {
      return T();
    }
    T elem = _elems[root()];
    return elem;
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    T orig = _elems[idx];
    _elems[idx] = elem;
    if (higherPriority(orig, elem)) {
      heapifyDown(idx);
    }
    else {
      heapifyUp(idx);
    }
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return (_elems.size() == 0);
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
      heaped.push_back(_elems[i]);
    }
}
