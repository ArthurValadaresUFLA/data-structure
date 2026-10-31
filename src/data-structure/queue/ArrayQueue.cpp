//
// Created by arthur on 20/06/24.
//

#include "data-structure/queue/ArrayQueue.h"

#include <stdexcept>
#include <utility>

template <class T> void ArrayQueue<T>::queue(T data) {
  if (this->_size == this->_capacity) {
    throw std::runtime_error("The array queue is full");
  }

  std::size_t tail = (this->_head + this->_size) % this->_capacity;
  this->_array[tail] = std::move(data);
  this->_size++;
}

template <class T> T ArrayQueue<T>::dequeue() {
  if (this->_size == 0) {
    throw std::runtime_error("The queue is empty");
  }

  T data = this->_array[this->_head];
  this->_head = (this->_head + 1) % this->_capacity;
  this->_size--;

  return data;
}

template <class T> std::size_t ArrayQueue<T>::size() const {
  return this->_size;
}

template <class T> bool ArrayQueue<T>::isEmpty() const {
  return this->_size == 0;
}

template <class T> T ArrayQueue<T>::peek() const {
  if (this->_size == 0) {
    throw std::runtime_error("The queue is empty");
  }

  return this->_array[this->_head];
}

template <class T> bool ArrayQueue<T>::isFull() const {
  return this->_size == this->_capacity;
}

template <class T> std::size_t ArrayQueue<T>::getCapacity() const {
  return this->_capacity;
}
