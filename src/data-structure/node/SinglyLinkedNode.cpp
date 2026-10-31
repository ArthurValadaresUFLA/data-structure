//
// Created by arthur on 19/06/24.
//

#include "data-structure/node/SinglyLinkedNode.h"

template <class T>
SinglyLinkedNodeInterface<T> *SinglyLinkedNode<T>::getNext() const {
  return this->_next;
}

template <class T>
void SinglyLinkedNode<T>::setNext(SinglyLinkedNodeInterface<T> *next) {
  this->_next = next;
}

template <class T> T SinglyLinkedNode<T>::getData() const {
  return this->_data;
}

template <class T> T &SinglyLinkedNode<T>::getDataRef() { return this->_data; }
