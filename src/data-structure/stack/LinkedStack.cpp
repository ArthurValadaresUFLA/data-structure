//
// Created by arthur on 22/06/24.
//

#include "data-structure/stack/LinkedStack.h"

#include <cstddef>
#include <stdexcept>

#include "data-structure/node/DoublyLinkedNode.h"

template <class T> void LinkedStack<T>::stackUp(T data) {
  DoublyLinkedNodeInterface<T> *node = new DoublyLinkedNode(data);

  if (this->_end == nullptr) {
    this->_end = node;
  } else {
    this->_end->setNext(node);
    node->setPrevious(this->_end);
    this->_end = node;
  }
}

template <class T> T LinkedStack<T>::unstack() {
  if (this->_end != nullptr) {
    T data = this->_end->getData();

    auto current = this->_end;
    this->_end = this->_end->getPrevious();

    delete current;
    this->_end->setNext(nullptr);

    return data;
  }

  throw std::runtime_error("The stack is empty");
}

template <class T> T LinkedStack<T>::peek() const {
  if (this->_end != nullptr) {
    return this->_end->getData();
  }
  throw std::runtime_error("The stack is empty");
}

template <class T> size_t LinkedStack<T>::size() const {
  const DoublyLinkedNodeInterface<T> *current = this->_begin;
  std::size_t i = 0;

  while (current != nullptr) {
    current = current->getNext();

    i++;
  }

  return i;
}

template <class T> bool LinkedStack<T>::empty() const {
  return this->_end == nullptr;
}
