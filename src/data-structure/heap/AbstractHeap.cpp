//
// Created by arthur on 14/08/24.
//

#include "data-structure/heap/AbstractHeap.h"

#include <stdexcept>

template <class T>
AbstractHeap<T>::AbstractHeap(const AbstractHeap &other)
    : _capacity(other._capacity), _top(nullptr) {
  _data = new T[_capacity];
  if (other._top != nullptr) {
    std::copy(other._data, other._data + _capacity, _data);
    _top = _data + (other._top - other._data);
  }
}

template <class T> size_t AbstractHeap<T>::parentOf(const size_t &index) {
  return (index - 1) / 2;
}

template <class T> size_t AbstractHeap<T>::rightChildOf(const size_t &index) {
  return 2 * index + 1;
}

template <class T> size_t AbstractHeap<T>::leftChildOf(const size_t &index) {
  return 2 * index + 2;
}

template <class T> T AbstractHeap<T>::peekRoot() const {
  return this->_data[0];
}

template <class T> bool AbstractHeap<T>::isFull() const {
  return this->_top == this->_data + this->_capacity;
}

template <class T> bool AbstractHeap<T>::isEmpty() const {
  return this->_top == nullptr;
}

template <class T> size_t AbstractHeap<T>::getCapacity() const {
  return this->_capacity;
}

template <class T> size_t AbstractHeap<T>::getSize() const {
  return this->_top - this->_data;
}

template <class T> T &AbstractHeap<T>::operator[](std::size_t index) const {
  if (index > this->getSize()) {
    throw std::out_of_range("Index out of range");
  }

  return this->_data[index];
}

template <class T>
bool AbstractHeap<T>::operator==(const AbstractHeap &other) const {
  if (this == &other) { // Verifica se os ponteiros são iguais
    return true;
  }

  if (_capacity != other._capacity) { // Verifica se têm a mesma capacidade
    return false;
  }

  for (std::size_t i = 0; i < _capacity; ++i) { // Compara os elementos
    if (_data[i] != other._data[i]) {
      return false;
    }
  }

  return true;
}
