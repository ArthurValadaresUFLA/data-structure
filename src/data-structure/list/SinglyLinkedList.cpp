//
// Created by arthur on 19/06/24.
//

#include "data-structure/list/SinglyLinkedList.h"

#include <stdexcept>

#include "data-structure/node/SinglyLinkedNode.h"

template <class T>
void SinglyLinkedList<T>::push(const T& data) {
  SinglyLinkedNode<T>* node = new SinglyLinkedNode(data);
  node->setNext(this->_begin);
  this->_begin = node;
}

template <class T>
void SinglyLinkedList<T>::pushBack(const T& data) {
  SinglyLinkedNode<T>* node = new SinglyLinkedNode(data);
  this->_end->setNext(node);
  this->_end = node;
}

template <class T>
void SinglyLinkedList<T>::insertAt(std::size_t index, const T& data) {
  auto current = this->_begin;
  SinglyLinkedNode<T>* previous = nullptr;
  std::size_t i = 0;

  while (current->getNext() != nullptr and i < index) {
    previous = current;
    current = current->getNext();

    i++;
  }

  SinglyLinkedNode<T>* node = new SinglyLinkedNode(data);

  if (previous == nullptr) {
    node->setNext(this->_begin);
    this->_begin = node;
  } else if (current->getNext() == nullptr) {
    current->setNext(node);
    this->_end = node;
  } else {
    previous->setNext(node);
    node->setNext(current);
  }
}

template <class T>
T SinglyLinkedList<T>::removeOnBegin() {
  if (this->_begin == nullptr) {
    throw std::runtime_error("Cannot remove on begin: the list is empty");
  }
  SinglyLinkedNode<T>* next = this->_begin->getNext();
  auto value = this->_begin->getData();
  this->_begin = next;
  return value;
}

template <class T>
T SinglyLinkedList<T>::removeAtEnd() {
  if (this->_end == nullptr) {
    throw std::runtime_error("Cannot remove at end: the list is empty");
  }
  T data = this->_end->getData();

  SinglyLinkedNode<T>* previous = nullptr;
  SinglyLinkedNode<T>* current = this->_begin;
  while (current->getNext() != nullptr) {
    previous = current;
    current = current->getNext();
  }

  if (previous != nullptr) {
    previous->setNext(nullptr);
  }

  this->_end = previous;

  return data;
}

template <class T>
T SinglyLinkedList<T>::removeAt(const std::size_t& position) {
  SinglyLinkedNode<T>* previous = nullptr;
  SinglyLinkedNode<T>* current = this->_begin;
  std::size_t i = 0;

  while (current->getNext() != nullptr and i < position) {
    previous = current;
    current = current->getNext();

    i++;
  }

  T data = current->getData();

  if (previous == nullptr) {
    this->_begin = current->getNext();
  } else if (current->getNext() == nullptr) {
    this->_end = previous;
  } else {
    previous->setNext(current->getNext());
  }

  return data;
}

template <class T>
bool SinglyLinkedList<T>::isEmpty() const {
  return this->_begin == nullptr and this->_end == nullptr;
}

template <class T>
bool SinglyLinkedList<T>::contains(const T& data) const {
  const SinglyLinkedNodeInterface<T>* current = this->_begin;

  while (current->getNext() != nullptr) {
    if (current->getData() == data) {
      return true;
    }

    current = current->getNext();
  }

  return false;
}

template <class T>
size_t SinglyLinkedList<T>::size() const {
  const SinglyLinkedNodeInterface<T>* current = this->_begin;
  std::size_t i = 0;

  while (current->getNext() != nullptr) {
    current = current->getNext();
    i++;
  }

  return i;
}

template <class T>
size_t SinglyLinkedList<T>::find(const T& data) const {
  const SinglyLinkedNodeInterface<T>* current = this->_begin;
  std::size_t i = 0;

  while (current->getNext() != nullptr and current->getData() != data) {
    current = current->getNext();
    i++;
  }

  return i;
}

template <class T>
T SinglyLinkedList<T>::operator[](std::size_t index) const {
  const SinglyLinkedNodeInterface<T>* current = this->_begin;
  std::size_t i = 0;

  while (current->getNext() != nullptr and i < index) {
    current = current->getNext();
    i++;
  }

  return current->getData();
}

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
  SinglyLinkedNodeInterface<T>* previous = nullptr;
  SinglyLinkedNodeInterface<T>* current = this->_begin;

  while (current != nullptr) {
    previous = current;
    current = current->getNext();
    delete previous;
  }
}
