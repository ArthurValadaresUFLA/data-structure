//
// Created by arthur on 22/06/24.
//

#include "data-structure/stack/ArrayStack.h"

#include <stdexcept>

template <class T> size_t ArrayStack<T>::size() const {
  if (this->_top == nullptr) {
    return 0;
  }

  return this->_top - this->_array;
}

template <class T> T ArrayStack<T>::peek() const {
  if (this->_top != nullptr) {
    return *(this->_top);
  }

  throw std::runtime_error("The array stack is empty");
}

template <class T> T ArrayStack<T>::unstack() {
  if (this->_top != nullptr) {
    T data = *(this->_top);
    this->_top--;
    return data;
  }
  throw std::runtime_error("The array stack is empty");
}

template <class T> void ArrayStack<T>::stackUp(T data) {
  if (this->_top != nullptr and this->_top < this->_array + this->_capacity) {
    this->_top++;
    *(this->_top) = data;
  } else if (this->_top == nullptr) {
    this->_top = this->_array;
    *(this->_top) = data;
  } else {
    throw std::runtime_error("The stack array is full");
  }
}

template <class T> bool ArrayStack<T>::empty() const {
  return this->_top == nullptr;
}
