//
// Created by arthur on 14/08/24.
//

#include "data-structure/heap/Tournament.h"

template <class T> void Tournament<T>::insert(const T &value) {
  if (this->isFull()) {
    throw std::runtime_error("The heap is full");
  }

  int index = this->getSize() + 1;
  this->data[index] = value;

  while (index != 0 and this->data[this->parent(index)] > this->data[index]) {
    std::swap(this->data[index], this->data[this->parent(index)]);
    index = this->parent(index);
  }
}
