//
// Created by arthur on 19/06/24.
//

#include "data-structure/list/SinglyLinkedList.h"

#include <stdexcept>
#include <utility>

#include "data-structure/node/SinglyLinkedNode.h"

template <class T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList &other)
    : AbstractSinglyLinkedList<T>(nullptr, nullptr) {
  // Se uma cópia falhar no meio do caminho (exceção em T ou em new), o
  // destrutor não será chamado para este objeto; por isso a limpeza é feita
  // aqui.
  try {
    for (const SinglyLinkedNodeInterface<T> *current = other._begin;
         current != nullptr; current = current->getNext()) {
      pushBack(current->getData());
    }
  } catch (...) {
    while (this->_begin != nullptr) {
      removeOnBegin();
    }
    throw;
  }
}

template <class T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList &&other) noexcept
    : AbstractSinglyLinkedList<T>(nullptr, nullptr) {
  swap(other);
}

template <class T>
SinglyLinkedList<T> &
SinglyLinkedList<T>::operator=(SinglyLinkedList other) noexcept {
  swap(other);
  return *this;
}

template <class T>
void SinglyLinkedList<T>::swap(SinglyLinkedList &other) noexcept {
  std::swap(this->_begin, other._begin);
  std::swap(this->_end, other._end);
  std::swap(this->_size, other._size);
}

template <class T> SinglyLinkedList<T>::~SinglyLinkedList() {
  SinglyLinkedNodeInterface<T> *current = this->_begin;

  while (current != nullptr) {
    SinglyLinkedNodeInterface<T> *next = current->getNext();
    delete current;
    current = next;
  }
}

template <class T> void SinglyLinkedList<T>::push(const T &data) {
  auto *node = new SinglyLinkedNode<T>(data, this->_begin);
  if (this->_end == nullptr) {
    this->_end = node;
  }
  this->_begin = node;
  this->_size++;
}

template <class T> void SinglyLinkedList<T>::pushBack(const T &data) {
  auto *node = new SinglyLinkedNode<T>(data);
  if (this->_end == nullptr) {
    this->_begin = node;
  } else {
    this->_end->setNext(node);
  }
  this->_end = node;
  this->_size++;
}

template <class T>
void SinglyLinkedList<T>::insertAt(std::size_t index, T data) {
  if (index == 0) {
    push(data);
    return;
  }
  if (index >= this->_size) {
    pushBack(data);
    return;
  }

  SinglyLinkedNodeInterface<T> *previous = this->_begin;
  for (std::size_t i = 1; i < index; i++) {
    previous = previous->getNext();
  }

  auto *node = new SinglyLinkedNode<T>(data, previous->getNext());
  previous->setNext(node);
  this->_size++;
}

template <class T> T SinglyLinkedList<T>::removeOnBegin() {
  if (this->_begin == nullptr) {
    throw std::runtime_error("Cannot remove on begin: the list is empty");
  }

  SinglyLinkedNodeInterface<T> *removed = this->_begin;
  T value = removed->getData();

  this->_begin = removed->getNext();
  if (this->_begin == nullptr) {
    this->_end = nullptr;
  }
  this->_size--;

  delete removed;
  return value;
}

template <class T> T SinglyLinkedList<T>::removeAtEnd() {
  if (this->_end == nullptr) {
    throw std::runtime_error("Cannot remove at end: the list is empty");
  }

  return removeAt(this->_size - 1);
}

template <class T> T SinglyLinkedList<T>::removeAt(std::size_t position) {
  if (position >= this->_size) {
    throw std::out_of_range("Cannot remove: index out of bounds");
  }
  if (position == 0) {
    return removeOnBegin();
  }

  SinglyLinkedNodeInterface<T> *previous = this->_begin;
  for (std::size_t i = 1; i < position; i++) {
    previous = previous->getNext();
  }

  SinglyLinkedNodeInterface<T> *removed = previous->getNext();
  T value = removed->getData();

  previous->setNext(removed->getNext());
  if (removed == this->_end) {
    this->_end = previous;
  }
  this->_size--;

  delete removed;
  return value;
}

template <class T> bool SinglyLinkedList<T>::isEmpty() const {
  return this->_size == 0;
}

template <class T> bool SinglyLinkedList<T>::contains(const T &data) const {
  return find(data) != this->_size;
}

template <class T> std::size_t SinglyLinkedList<T>::size() const {
  return this->_size;
}

template <class T> std::size_t SinglyLinkedList<T>::find(const T &data) const {
  const SinglyLinkedNodeInterface<T> *current = this->_begin;
  std::size_t i = 0;

  while (current != nullptr and not(current->getData() == data)) {
    current = current->getNext();
    i++;
  }

  return i;
}

template <class T> T &SinglyLinkedList<T>::operator[](std::size_t index) const {
  if (index >= this->_size) {
    throw std::out_of_range("Index out of bounds");
  }

  SinglyLinkedNodeInterface<T> *current = this->_begin;
  for (std::size_t i = 0; i < index; i++) {
    current = current->getNext();
  }

  return current->getDataRef();
}

template <class T>
void SinglyLinkedList<T>::removeWhere(
    std::function<bool(std::size_t, T)> predicate) {
  SinglyLinkedNodeInterface<T> *previous = nullptr;
  SinglyLinkedNodeInterface<T> *current = this->_begin;
  std::size_t index = 0;

  while (current != nullptr) {
    SinglyLinkedNodeInterface<T> *next = current->getNext();

    if (predicate(index, current->getData())) {
      if (previous == nullptr) {
        this->_begin = next;
      } else {
        previous->setNext(next);
      }
      if (current == this->_end) {
        this->_end = previous;
      }
      this->_size--;
      delete current;
    } else {
      previous = current;
    }

    current = next;
    index++;
  }
}
