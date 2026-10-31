//
// Created by arthur on 14/08/24.
//

#include "data-structure/heap/MaxHeap.h"

#include <stdexcept>

template <class T> MaxHeap<T> MaxHeap<T>::from(const T *array, std::size_t n) {
  MaxHeap<T> heap(n);
  for (std::size_t i = 0; i < n; i++) {
    heap.insert(array[i]);
  }
  return heap;
}

template <class T> T MaxHeap<T>::removeRoot() {
  return this->popSorted([](const T &a, const T &b) { return a > b; });
}

template <class T> void MaxHeap<T>::insert(const T &value) {
  this->pushSorted(value, [](const T &a, const T &b) { return a > b; });
}
