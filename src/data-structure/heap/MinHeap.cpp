//
// Created by arthur on 14/08/24.
//

#include "data-structure/heap/MinHeap.h"

#include <stdexcept>

template <class T>
template <std::size_t N>
MinHeap<T> MinHeap<T>::from(const T *array) {
  MinHeap<T> heap = MinHeap<T>(N);
  for (std::size_t i = 0; i < N; i++) {
    heap.insert(array[i]);
  }
  return heap;
}

template <class T> T MinHeap<T>::removeRoot() const {
  static const std::string HEAP_EMPTY_ERROR =
      "Heap is empty, cannot remove root.";

  if (this->isEmpty()) {
    throw std::out_of_range(HEAP_EMPTY_ERROR);
  }

  T root = this->_data[0];
  this->_data[0] = this->_data[this->getSize() - 1];
  auto heapSize = this->getSize() - 1;
  std::size_t currNode = 0;

  while (true) {
    std::size_t leftChild = this->leftChildOf(currNode);
    std::size_t rightChild = this->rightChildOf(currNode);

    std::size_t smallestChild =
        findSmallestChild(currNode, leftChild, rightChild, heapSize);

    if (smallestChild == currNode) {
      break;
    }

    std::swap(this->_data[currNode], this->_data[smallestChild]);
    currNode = smallestChild;
  }

  return root;
}

template <class T>
std::size_t MinHeap<T>::findSmallestChild(std::size_t currNode,
                                          std::size_t leftChild,
                                          std::size_t rightChild,
                                          std::size_t heapSize) const {
  std::size_t smallestChild =
      (leftChild < heapSize && this->_data[leftChild] < this->_data[currNode])
          ? leftChild
          : currNode;
  smallestChild = (rightChild < heapSize &&
                   this->_data[rightChild] < this->_data[smallestChild])
                      ? rightChild
                      : smallestChild;
  return smallestChild;
}

template <class T> void MinHeap<T>::insert(const T &value) {
  std::size_t hole = this->getSize();
  while (hole > 0 && value < this->_data[this->parentOf(hole)]) {
    this->_data[hole] = this->_data[this->parentOf(hole)];
    hole = this->parentOf(hole);
  }
  this->_data[hole] = value;
}
