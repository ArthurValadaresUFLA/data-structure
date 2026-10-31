//
// Created by arthur on 29/07/24.
//

#include "data-structure/hash/OpenAddressHashTable.h"

#include <stdexcept>
#include <utility>

template <class T>
OpenAddressHashTable<T>::OpenAddressHashTable(
    std::size_t capacity,
    std::function<std::size_t(T, std::size_t)> hashFunction)
    : AbstractHashTable<T>(capacity, std::move(hashFunction)),
      _table(capacity) {}

template <class T>
std::size_t OpenAddressHashTable<T>::locate(const T &value) const {
  std::size_t start = this->indexOf(value);

  for (std::size_t step = 0; step < this->_capacity; step++) {
    std::size_t index = (start + step) % this->_capacity;
    const Slot &slot = _table[index];

    if (slot.value.has_value()) {
      if (*slot.value == value) {
        return index;
      }
    } else if (not slot.removed) {
      return this->_capacity; // posição nunca usada: o valor não está aqui
    }
  }

  return this->_capacity;
}

template <class T> bool OpenAddressHashTable<T>::isFull() const {
  return _size == this->_capacity;
}

template <class T>
bool OpenAddressHashTable<T>::contains(const T &value) const {
  return locate(value) != this->_capacity;
}

template <class T> void OpenAddressHashTable<T>::add(const T &value) {
  if (contains(value)) {
    return;
  }
  if (isFull()) {
    throw std::runtime_error("The hash table is full");
  }

  std::size_t start = this->indexOf(value);
  for (std::size_t step = 0; step < this->_capacity; step++) {
    Slot &slot = _table[(start + step) % this->_capacity];

    if (not slot.value.has_value()) { // livre ou lápide: pode reaproveitar
      slot.value = value;
      slot.removed = false;
      _size++;
      return;
    }
  }
}

template <class T> void OpenAddressHashTable<T>::remove(const T &value) {
  std::size_t index = locate(value);
  if (index != this->_capacity) {
    _table[index].value.reset();
    _table[index].removed = true;
    _size--;
  }
}
