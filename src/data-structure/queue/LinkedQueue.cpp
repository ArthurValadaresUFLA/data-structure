//
// Created by arthur on 20/06/24.
//

#include "data-structure/queue/LinkedQueue.h"

#include <stdexcept>
#include <utility>

template <class T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue &other)
    : AbstractLinkedQueue<T>(nullptr, nullptr) {
  try {
    for (const SinglyLinkedNodeInterface<T> *current = other._begin;
         current != nullptr; current = current->getNext()) {
      queue(current->getData());
    }
  } catch (...) {
    // o destrutor não roda para objetos cujo construtor lançou exceção
    while (this->_begin != nullptr) {
      dequeue();
    }
    throw;
  }
}

template <class T>
LinkedQueue<T>::LinkedQueue(LinkedQueue &&other) noexcept
    : AbstractLinkedQueue<T>(nullptr, nullptr) {
  swap(other);
}

template <class T>
LinkedQueue<T> &LinkedQueue<T>::operator=(LinkedQueue other) noexcept {
  swap(other);
  return *this;
}

template <class T> void LinkedQueue<T>::swap(LinkedQueue &other) noexcept {
  std::swap(this->_begin, other._begin);
  std::swap(this->_end, other._end);
  std::swap(this->_size, other._size);
}

template <class T> LinkedQueue<T>::~LinkedQueue() {
  SinglyLinkedNodeInterface<T> *current = this->_begin;

  while (current != nullptr) {
    SinglyLinkedNodeInterface<T> *next = current->getNext();
    delete current;
    current = next;
  }
}

template <class T> void LinkedQueue<T>::queue(T data) {
  auto *node = new SinglyLinkedNode<T>(std::move(data));

  if (this->_end == nullptr) {
    this->_begin = node;
  } else {
    this->_end->setNext(node);
  }
  this->_end = node;
  this->_size++;
}

template <class T> T LinkedQueue<T>::dequeue() {
  if (this->_begin == nullptr) {
    throw std::runtime_error("The queue is empty");
  }

  SinglyLinkedNodeInterface<T> *removed = this->_begin;
  T data = removed->getData();

  this->_begin = removed->getNext();
  if (this->_begin == nullptr) {
    this->_end = nullptr;
  }
  this->_size--;
  delete removed;

  return data;
}

template <class T> std::size_t LinkedQueue<T>::size() const {
  return this->_size;
}

template <class T> bool LinkedQueue<T>::isEmpty() const {
  return this->_begin == nullptr;
}

template <class T> T LinkedQueue<T>::peek() const {
  if (this->_begin == nullptr) {
    throw std::runtime_error("The queue is empty");
  }

  return this->_begin->getData();
}
