//
// Created by arthur on 14/08/24.
//

#include "data-structure/heap/AbstractHeap.h"

#include <stdexcept>

template <class T>
std::size_t AbstractHeap<T>::parentOf(const std::size_t &index) const {
  return index == 0 ? 0 : (index - 1) / 2;
}

template <class T>
std::size_t AbstractHeap<T>::rightChildOf(const std::size_t &index) const {
  return 2 * index + 2;
}

template <class T>
std::size_t AbstractHeap<T>::leftChildOf(const std::size_t &index) const {
  return 2 * index + 1;
}

template <class T> T AbstractHeap<T>::peekRoot() const {
  if (this->_size == 0) {
    throw std::out_of_range("Heap is empty, cannot peek root.");
  }

  return this->_data[0];
}

template <class T> bool AbstractHeap<T>::isFull() const {
  return this->_size == this->_capacity;
}

template <class T> bool AbstractHeap<T>::isEmpty() const {
  return this->_size == 0;
}

template <class T> std::size_t AbstractHeap<T>::getCapacity() const {
  return this->_capacity;
}

template <class T> std::size_t AbstractHeap<T>::getSize() const {
  return this->_size;
}

template <class T> T &AbstractHeap<T>::operator[](std::size_t index) const {
  if (index >= this->_size) {
    throw std::out_of_range("Index out of range");
  }

  return this->_data[index];
}

template <class T>
bool AbstractHeap<T>::operator==(const AbstractHeap &other) const {
  if (this == &other) {
    return true;
  }

  if (_capacity != other._capacity or _size != other._size) {
    return false;
  }

  for (std::size_t i = 0; i < _size; ++i) {
    if (not(_data[i] == other._data[i])) {
      return false;
    }
  }

  return true;
}
