//
// Created by arthur on 29/07/24.
//

#include "data-structure/hash/LinkedHashTable.h"

#include <utility>

template <class T>
LinkedHashTable<T>::LinkedHashTable(
    std::size_t capacity,
    std::function<std::size_t(T, std::size_t)> hashFunction)
    : AbstractHashTable<T>(capacity, std::move(hashFunction)),
      _table(capacity) {}

template <class T> void LinkedHashTable<T>::add(const T &value) {
  auto &bucket = _table[this->indexOf(value)];
  if (not bucket.contains(value)) {
    bucket.pushBack(value);
  }
}

template <class T> bool LinkedHashTable<T>::contains(const T &value) const {
  return _table[this->indexOf(value)].contains(value);
}

template <class T> void LinkedHashTable<T>::remove(const T &value) {
  _table[this->indexOf(value)].removeWhere(
      [&value](std::size_t, T storedValue) { return storedValue == value; });
}

template <class T>
DoublyLinkedList<T> &LinkedHashTable<T>::withHashOf(const T &value) {
  return _table[this->indexOf(value)];
}
