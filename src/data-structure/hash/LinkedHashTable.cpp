#include "data-structure/hash/LinkedHashTable.h"
#include "data-structure/hash/AbstractHashTable.h"

template <class T>
LinkedHashTable<T>::LinkedHashTable(
    std::size_t capacity,
    std::function<std::size_t(T, std::size_t)> hashFunction)
    : AbstractHashTable<T>(capacity, hashFunction) {
  table = new DoublyLinkedList<T>[capacity];
}

template <class T>
LinkedHashTable<T>::LinkedHashTable(const LinkedHashTable<T> &other)
    : AbstractHashTable<T>(other._capacity, other._hashFunction) {
  table = new DoublyLinkedList<T>[this->_capacity];
  for (std::size_t i = 0; i < this->_capacity; ++i) {
    table[i] = other.table[i];
  }
}

template <class T> void LinkedHashTable<T>::add(const T &value) {
  auto index = _hashFunction(value, this->_capacity);
  table[index].pushBack(value);
}

template <class T> bool LinkedHashTable<T>::contains(const T &value) const {
  auto index = _hashFunction(value, this->_capacity);
  return table[index].contains(value);
}

template <class T> void LinkedHashTable<T>::remove(const T &value) const {
  auto index = _hashFunction(value, this->_capacity);
  table[index].removeWhere(
      [&value](std::size_t _, T storedValue) { return storedValue == value; });
}

template <class T>
DoublyLinkedList<T> &LinkedHashTable<T>::withHashOf(const T &value) {
  auto index = _hashFunction(value, this->_capacity);
  return table[index];
}

template <class T>
LinkedHashTable<T> &
LinkedHashTable<T>::operator=(const LinkedHashTable<T> &other) {
  if (this == &other) {
    return *this; // Auto-atribuição, retorne *this.
  }

  // Limpe a tabela hash atual.
  delete[] table;
  table = nullptr;

  // Copie a capacidade e a função hash do outro objeto.
  this->_capacity = other._capacity;
  this->_hashFunction = other._hashFunction;

  // Aloca nova memória para a tabela e copia os conteúdos do outro objeto.
  if (other.table) {
    table = new DoublyLinkedList<T>[other._capacity];
    for (std::size_t i = 0; i < other._capacity; ++i) {
      table[i] = other.table[i];
    }
  } else {
    table = nullptr;
  }

  return *this;
}
