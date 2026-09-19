//
// Created by arthur on 19/06/24.
//

#include "data-structure/node/DoublyLinkedNode.h"

template <class T>
DoublyLinkedNodeInterface<T> *DoublyLinkedNode<T>::getPrevious() const {
  return this->_previous;
}

template <class T>
DoublyLinkedNodeInterface<T> *DoublyLinkedNode<T>::getNext() const {
  return this->_next;
}

template <class T>
T DoublyLinkedNode<T>::getData() const {
  return this->_data;
}

template <class T>
void DoublyLinkedNode<T>::setPrevious(DoublyLinkedNodeInterface<T> *previous) {
  this->_previous = previous;
}

template <class T>
void DoublyLinkedNode<T>::setNext(DoublyLinkedNodeInterface<T> *next) {
  this->_next = next;
}

template <class T>
std::tuple<DoublyLinkedNodeInterface<T> *, DoublyLinkedNodeInterface<T> *>
DoublyLinkedNode<T>::getBoth() const {
  return std::make_tuple(this->_previous, this->_next);
}
