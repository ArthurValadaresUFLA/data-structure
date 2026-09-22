//
// Created by arthur on 20/06/24.
//

#include "data-structure/queue/LinkedQueue.h"

template <class T> void LinkedQueue<T>::queue(T data) {
  DoublyLinkedNodeInterface<T> node = new DoublyLinkedNode(data);
  if (this->_end == nullptr) {
    this->_end = node;
    this->_begin = node;
  } else {
    this->_end->setPrevious(node);
    node.setNext(this->_end);
    this->_end = node;
  }
}

template <class T> T LinkedQueue<T>::dequeue() {
  if (this->_begin == nullptr) {
    return nullptr;
  }

  DoublyLinkedNodeInterface<T> next = this->_begin->getNext();
  T data = this->_begin->getData();
  delete this->_begin;
  this->_begin = next;

  return data;
}

template <class T> size_t LinkedQueue<T>::size() const {
  DoublyLinkedNodeInterface<T> current = this->_begin;
  std::size_t i = 0;
  while (current.getNext() != nullptr) {
    current = current.getNext();
    i++;
  }

  return i;
}

template <class T> bool LinkedQueue<T>::isEmpty() const {
  return this->_begin == nullptr and this->_end == nullptr;
}

template <class T> T LinkedQueue<T>::peek() const { return *(this->_end); }
