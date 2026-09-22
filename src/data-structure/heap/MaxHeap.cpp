//
// Created by arthur on 14/08/24.
//

#include "data-structure/heap/MaxHeap.h"

#include <stdexcept>

template <class T>
MaxHeap<T>::MaxHeap(const size_t &capacity) : AbstractHeap<T>(capacity) {}

template <class T>
template <std::size_t N>
MaxHeap<T> MaxHeap<T>::from(const T *array) {
  MaxHeap<T> heap = MaxHeap<T>(N);
  for (std::size_t i = 0; i < N; i++) {
    heap.insert(array[i]);
  }
  return heap;
}

template <class T> T MaxHeap<T>::removeRoot() const {
  if (this->isEmpty()) {
    throw std::out_of_range("Heap is empty, cannot remove root.");
  }

  // Store the root node.
  T root = this->_data[0];

  // Move the last element to root.
  this->_data[0] = this->_data[this->getSize() - 1];

  std::size_t heapSize = this->getSize() - 1;

  std::size_t currNode = 0;

  while (true) {
    std::size_t leftChild = this->leftChildOf(currNode);
    std::size_t rightChild = this->rightChildOf(currNode);

    std::size_t largerChild =
        (leftChild<heapSize and this->_data[leftChild]> this->_data[currNode])
            ? leftChild
            : currNode;
    largerChild = (rightChild<heapSize and this->_data[rightChild]> this
                       ->_data[largerChild])
                      ? rightChild
                      : largerChild;

    if (largerChild == currNode) {
      break;
    }

    std::swap(this->_data[currNode], this->_data[largerChild]);
    currNode = largerChild;
  }

  return root;
}

template <class T> void MaxHeap<T>::insert(const T &value) {
  size_t hole = this->getSize();
  while (hole > 0 && value > this->_data[this->parentOf(hole)]) {
    this->_data[hole] = this->_data[this->parentOf(hole)];
    hole = this->parentOf(hole);
  }
  this->_data[hole] = value;
}
