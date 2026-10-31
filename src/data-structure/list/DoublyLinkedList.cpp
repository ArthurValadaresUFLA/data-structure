//
// Created by arthur on 20/06/24.
//

#include "data-structure/list/DoublyLinkedList.h"

#include <stdexcept>
#include <utility>

#include "data-structure/node/DoublyLinkedNode.h"

template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList &other)
    : AbstractDoublyLinkedList<T>(nullptr, nullptr) {
  // Se uma cópia falhar no meio do caminho (exceção em T ou em new), o
  // destrutor não será chamado para este objeto; por isso a limpeza é feita
  // aqui.
  try {
    for (const DoublyLinkedNodeInterface<T> *current = other._begin;
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
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList &&other) noexcept
    : AbstractDoublyLinkedList<T>(nullptr, nullptr) {
  swap(other);
}

template <class T>
DoublyLinkedList<T> &
DoublyLinkedList<T>::operator=(DoublyLinkedList other) noexcept {
  swap(other);
  return *this;
}

template <class T>
void DoublyLinkedList<T>::swap(DoublyLinkedList &other) noexcept {
  std::swap(this->_begin, other._begin);
  std::swap(this->_end, other._end);
  std::swap(this->_size, other._size);
}

template <class T> DoublyLinkedList<T>::~DoublyLinkedList() {
  DoublyLinkedNodeInterface<T> *current = this->_begin;

  while (current != nullptr) {
    DoublyLinkedNodeInterface<T> *next = current->getNext();
    delete current;
    current = next;
  }
}

template <class T> void DoublyLinkedList<T>::push(const T &data) {
  auto *node = new DoublyLinkedNode<T>(data);

  node->setNext(this->_begin);
  if (this->_begin == nullptr) {
    this->_end = node;
  } else {
    this->_begin->setPrevious(node);
  }
  this->_begin = node;
  this->_size++;
}

template <class T> void DoublyLinkedList<T>::pushBack(const T &data) {
  auto *node = new DoublyLinkedNode<T>(data);

  node->setPrevious(this->_end);
  if (this->_end == nullptr) {
    this->_begin = node;
  } else {
    this->_end->setNext(node);
  }
  this->_end = node;
  this->_size++;
}

template <class T>
void DoublyLinkedList<T>::insertAt(std::size_t index, T data) {
  if (index == 0) {
    push(data);
    return;
  }
  if (index >= this->_size) {
    pushBack(data);
    return;
  }

  // 0 < index < size: existem nós antes e depois da nova posição
  DoublyLinkedNodeInterface<T> *current = this->_begin;
  for (std::size_t i = 0; i < index; i++) {
    current = current->getNext();
  }
  DoublyLinkedNodeInterface<T> *previous = current->getPrevious();

  auto *node = new DoublyLinkedNode<T>(data);
  node->setPrevious(previous);
  node->setNext(current);
  previous->setNext(node);
  current->setPrevious(node);
  this->_size++;
}

template <class T> T DoublyLinkedList<T>::removeOnBegin() {
  if (this->_begin == nullptr) {
    throw std::runtime_error("Cannot remove on begin: the list is empty");
  }

  DoublyLinkedNodeInterface<T> *removed = this->_begin;
  T value = removed->getData();

  this->_begin = removed->getNext();
  if (this->_begin == nullptr) {
    this->_end = nullptr;
  } else {
    this->_begin->setPrevious(nullptr);
  }
  this->_size--;

  delete removed;
  return value;
}

template <class T> T DoublyLinkedList<T>::removeAtEnd() {
  if (this->_end == nullptr) {
    throw std::runtime_error("Cannot remove at end: the list is empty");
  }

  DoublyLinkedNodeInterface<T> *removed = this->_end;
  T value = removed->getData();

  this->_end = removed->getPrevious();
  if (this->_end == nullptr) {
    this->_begin = nullptr;
  } else {
    this->_end->setNext(nullptr);
  }
  this->_size--;

  delete removed;
  return value;
}

template <class T> T DoublyLinkedList<T>::removeAt(std::size_t position) {
  if (position >= this->_size) {
    throw std::out_of_range("Cannot remove: index out of bounds");
  }
  if (position == 0) {
    return removeOnBegin();
  }
  if (position == this->_size - 1) {
    return removeAtEnd();
  }

  // 0 < position < size - 1: o nó possui vizinhos nos dois lados
  DoublyLinkedNodeInterface<T> *current = this->_begin;
  for (std::size_t i = 0; i < position; i++) {
    current = current->getNext();
  }

  DoublyLinkedNodeInterface<T> *previous = current->getPrevious();
  DoublyLinkedNodeInterface<T> *next = current->getNext();
  T value = current->getData();

  previous->setNext(next);
  next->setPrevious(previous);
  this->_size--;

  delete current;
  return value;
}

template <class T> bool DoublyLinkedList<T>::isEmpty() const {
  return this->_size == 0;
}

template <class T> std::size_t DoublyLinkedList<T>::find(const T &data) const {
  const DoublyLinkedNodeInterface<T> *current = this->_begin;
  std::size_t i = 0;

  while (current != nullptr and not(current->getData() == data)) {
    current = current->getNext();
    i++;
  }

  return i;
}

template <class T> std::size_t DoublyLinkedList<T>::size() const {
  return this->_size;
}

template <class T> bool DoublyLinkedList<T>::contains(const T &data) const {
  return find(data) != this->_size;
}

template <class T> T &DoublyLinkedList<T>::operator[](std::size_t index) const {
  if (index >= this->_size) {
    throw std::out_of_range("Index out of bounds");
  }

  DoublyLinkedNodeInterface<T> *current = this->_begin;
  for (std::size_t i = 0; i < index; i++) {
    current = current->getNext();
  }

  return current->getDataRef();
}

template <class T>
void DoublyLinkedList<T>::removeWhere(
    std::function<bool(std::size_t, T)> predicate) {
  std::size_t index = 0;
  DoublyLinkedNodeInterface<T> *current = this->_begin;

  while (current != nullptr) {
    DoublyLinkedNodeInterface<T> *next = current->getNext();

    if (predicate(index, current->getData())) {
      DoublyLinkedNodeInterface<T> *previous = current->getPrevious();

      if (previous == nullptr) {
        this->_begin = next;
      } else {
        previous->setNext(next);
      }
      if (next == nullptr) {
        this->_end = previous;
      } else {
        next->setPrevious(previous);
      }
      this->_size--;

      delete current;
    }

    current = next;
    index++;
  }
}
