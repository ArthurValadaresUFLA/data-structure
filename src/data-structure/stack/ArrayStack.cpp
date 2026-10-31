//
// Created by arthur on 22/06/24.
//

#include "data-structure/stack/ArrayStack.h"

#include <stdexcept>

template <class T> std::size_t ArrayStack<T>::size() const {
  return this->_size;
}

template <class T> T ArrayStack<T>::peek() const {
  if (this->_size == 0) {
    throw std::runtime_error("The array stack is empty");
  }

  return this->_array[this->_size - 1];
}

template <class T> T ArrayStack<T>::unstack() {
  if (this->_size == 0) {
    throw std::runtime_error("The array stack is empty");
  }

  return this->_array[--this->_size];
}

template <class T> void ArrayStack<T>::stackUp(T data) {
  if (this->_size == this->_capacity) {
    throw std::runtime_error("The stack array is full");
  }

  this->_array[this->_size++] = std::move(data);
}

template <class T> bool ArrayStack<T>::empty() const {
  return this->_size == 0;
}

template <class T> bool ArrayStack<T>::isFull() const {
  return this->_size == this->_capacity;
}

template <class T> std::size_t ArrayStack<T>::getCapacity() const {
  return this->_capacity;
}
