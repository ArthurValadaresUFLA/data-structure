//
// Created by arthur on 20/06/24.
//

#include "data-structure/queue/ArrayQueue.h"

#include <stdexcept>

template <class T> ArrayQueue<T>::~ArrayQueue() { delete[] this->array; }

template <class T> void ArrayQueue<T>::queue(T data) {
  if (this->_begin == nullptr and this->_end == nullptr) {
    this->array[0] = data;
    this->_begin = &(this->array)[0];
    this->_end = &(this->array)[0];
  } else if (this->_end - this->_begin < this->_capacity and
             this->_end - this->array < this->_capacitys) {
    this->_end++;
    *(this->_end) = data;
  } else if (this->_end - this->_begin < this->_capacity and
             this->_end - this->array == this->_capacity) {
    this->_end = (this->_end + 1 - this->array) % this->_capacity + this->array;
    *(this->_end) = data;
  } else {
    throw std::runtime_error("The _array queue is full");
  }
}

template <class T> T ArrayQueue<T>::dequeue() {
  if (this->_begin == this->_end and this->_begin != nullptr) {
    T data = *(this->_begin);

    this->_begin = nullptr;
    this->_end = nullptr;

    return data;
  } else if (this->_begin == this->_end and this->_begin == nullptr) {
    throw std::runtime_error("The queue is empty");
  } else {
    T data = *(this->_begin);
    this->_begin =
        (this->_begin + 1 - this->array) % this->_capacity + this->array;
    return data;
  }
}

template <class T> size_t ArrayQueue<T>::size() const {
  if (this->_end > this->_begin) {
    return this->_end - this->_begin;
  }

  return (this->_end - this->array) +
         (this->array + this->_capacity - this->_begin);
}

template <class T> bool ArrayQueue<T>::isEmpty() const {
  return this->_end == nullptr and this->_begin == nullptr;
}

template <class T> T ArrayQueue<T>::peek() const { return *(this->_begin); }
