//
// Created by arthur on 22/06/24.
//

#include "data-structure/stack/LinkedStack.h"

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

#include "data-structure/node/SinglyLinkedNode.h"

template <class T>
LinkedStack<T>::LinkedStack(const LinkedStack &other)
    : AbstractLinkedStack<T>(nullptr) {
  // Os nós são percorridos do topo para a base; para reproduzir a mesma ordem
  // é preciso empilhar da base para o topo.
  std::vector<T> values;
  values.reserve(other._size);
  for (const SinglyLinkedNodeInterface<T> *current = other._top;
       current != nullptr; current = current->getNext()) {
    values.push_back(current->getData());
  }

  try {
    for (auto it = values.rbegin(); it != values.rend(); ++it) {
      stackUp(*it);
    }
  } catch (...) {
    // o destrutor não roda para objetos cujo construtor lançou exceção
    while (this->_top != nullptr) {
      unstack();
    }
    throw;
  }
}

template <class T>
LinkedStack<T>::LinkedStack(LinkedStack &&other) noexcept
    : AbstractLinkedStack<T>(nullptr) {
  swap(other);
}

template <class T>
LinkedStack<T> &LinkedStack<T>::operator=(LinkedStack other) noexcept {
  swap(other);
  return *this;
}

template <class T> void LinkedStack<T>::swap(LinkedStack &other) noexcept {
  std::swap(this->_top, other._top);
  std::swap(this->_size, other._size);
}

template <class T> LinkedStack<T>::~LinkedStack() {
  SinglyLinkedNodeInterface<T> *current = this->_top;

  while (current != nullptr) {
    SinglyLinkedNodeInterface<T> *below = current->getNext();
    delete current;
    current = below;
  }
}

template <class T> void LinkedStack<T>::stackUp(T data) {
  this->_top = new SinglyLinkedNode<T>(std::move(data), this->_top);
  this->_size++;
}

template <class T> T LinkedStack<T>::unstack() {
  if (this->_top == nullptr) {
    throw std::runtime_error("The stack is empty");
  }

  SinglyLinkedNodeInterface<T> *removed = this->_top;
  T data = removed->getData();

  this->_top = removed->getNext();
  this->_size--;
  delete removed;

  return data;
}

template <class T> T LinkedStack<T>::peek() const {
  if (this->_top == nullptr) {
    throw std::runtime_error("The stack is empty");
  }

  return this->_top->getData();
}

template <class T> std::size_t LinkedStack<T>::size() const {
  return this->_size;
}

template <class T> bool LinkedStack<T>::empty() const {
  return this->_top == nullptr;
}
