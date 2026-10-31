//
// Created by arthur on 14/08/24.
//

#include "data-structure/heap/MinHeap.h"

#include <stdexcept>

template <class T> MinHeap<T> MinHeap<T>::from(const T *array, std::size_t n) {
  MinHeap<T> heap(n);
  for (std::size_t i = 0; i < n; i++) {
    heap.insert(array[i]);
  }
  return heap;
}

template <class T> T MinHeap<T>::removeRoot() {
  return this->popSorted([](const T &a, const T &b) { return a < b; });
}

template <class T> void MinHeap<T>::insert(const T &value) {
  this->pushSorted(value, [](const T &a, const T &b) { return a < b; });
}
