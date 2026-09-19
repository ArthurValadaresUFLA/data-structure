//
// Created by arthur on 20/06/24.
//

#include "data-structure/list/DoublyLinkedList.h"

#include <stdexcept>

#include "data-structure/node/DoublyLinkedNode.h"

template <class T>
void DoublyLinkedList<T>::push(const T &data) {
  DoublyLinkedNode<T> *node = new DoublyLinkedNode(data);
  node->setNext(this->_begin);
  this->_begin = node;
}

template <class T>
void DoublyLinkedList<T>::pushBack(const T &data) {
  DoublyLinkedNode<T> *node = new DoublyLinkedNode(data);
  node->setPrevious(this->_end);
  this->_end = node;
}

template <class T>
void DoublyLinkedList<T>::insertAt(std::size_t index, T data) {
  DoublyLinkedNode<T> *current = this->_begin;
  std::size_t i = 0;

  while (current->getNext() != nullptr and i < index) {
    current = current->getNext();
  }

  DoublyLinkedNode<T> *node = new DoublyLinkedNode(data);
  DoublyLinkedNode<T> *previous = current->getPrevious();
  node->setPrevious(previous);
  previous->setNext(node);
  current->setPrevious(node);
}

template <class T>
T DoublyLinkedList<T>::removeOnBegin() {
  auto current = this->_begin;
  this->_begin = current->getNext();

  T value = current->getData();
  delete current;

  return value;
}

template <class T>
T DoublyLinkedList<T>::removeAtEnd() {
  auto current = this->_end;
  this->_end = current->getPrevious();

  T value = current->getData();
  delete current;

  return value;
}

template <class T>
T DoublyLinkedList<T>::removeAt(const std::size_t &position) {
  DoublyLinkedNode<T> *current = this->_begin;
  std::size_t i = 0;

  while (current->getNext() != nullptr and i < position) {
    current = current->getNext();
  }

  if (i == position) {
    auto [previous, next] = current->getBoth();

    T value = current->getData();
    previous->setNext(next);
    next->setPrevious(previous);

    delete current;

    return value;
  }

  throw std::runtime_error("Index out of bounds");
}

template <class T>
bool DoublyLinkedList<T>::isEmpty() const {
  return this->_begin == nullptr and this->_end == nullptr;
}

template <class T>
size_t DoublyLinkedList<T>::find(const T &data) const {
  const DoublyLinkedNodeInterface<T> *current = this->_begin;
  std::size_t i = 0;

  while (current->getNext() != nullptr and current->getData() != data) {
    current = current->getNext();
    i++;
  }

  return i;
}

template <class T>
size_t DoublyLinkedList<T>::size() const {
  const DoublyLinkedNodeInterface<T> *current = this->_begin;
  std::size_t i = 0;

  while (current->getNext() != nullptr) {
    current = current->getNext();
    i++;
  }

  return i;
}

template <class T>
bool DoublyLinkedList<T>::contains(const T &data) const {
  const DoublyLinkedNodeInterface<T> *current = this->_begin;

  while (current->getNext() != nullptr) {
    if (current->getData() == data) {
      return true;
    }
    current = current->getNext();
  }

  return false;
}

template <class T>
T &DoublyLinkedList<T>::operator[](std::size_t index) const {
  const DoublyLinkedNodeInterface<T> *current = this->_begin;
  std::size_t i = 0;

  while (current->getNext() != nullptr and i < index) {
    current = current->getNext();
    i++;
  }

  if (i == index) {
    return current->getData();
  }

  throw std::runtime_error("Index out of bounds");
}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  DoublyLinkedNodeInterface<T> *previous = nullptr;
  DoublyLinkedNodeInterface<T> *current = this->_begin;

  while (current != nullptr) {
    previous = current;
    current = current->getNext();
    delete previous;
  }
}

template <class T>
void DoublyLinkedList<T>::removeWhere(
    std::function<bool(std::size_t, T)> predicate) {
  std::size_t index = 0;
  DoublyLinkedNodeInterface<T> *current = this->_begin;
  while (current != nullptr) {
    if (predicate(index, current->getData())) {
      auto previous = current->getPrevious();
      auto next = current->getNext();

      previous->setNext(next);
      next->setPrevious(previous);

      delete current;
      current = next;
    } else {
      current = current->getNext();
    }
    index++;
  }
}
