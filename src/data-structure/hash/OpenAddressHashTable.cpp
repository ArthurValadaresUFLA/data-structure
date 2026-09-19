#include "data-structure/hash/OpenAddressHashTable.h"

#include <algorithm>

template<class T>
OpenAddressHashTable<T>::OpenAddressHashTable(
        std::size_t capacity, std::function<std::size_t(T, std::size_t)> hashFunction)
        : AbstractHashTable<T>(capacity, hashFunction) {
    _table = new T[capacity];
}

template<class T>
bool OpenAddressHashTable<T>::isFull() const {
    return std::any_of(_table, _table + this->_capacity,
                       [](const T &storedValue) { return not storedValue; });
}

template<class T>
bool OpenAddressHashTable<T>::contains(const T &value) const {
    return std::any_of(
            _table, _table + this->_capacity,
            [&value](const T &storedValue) { return storedValue == value; });
}

template<class T>
void OpenAddressHashTable<T>::add(const T &value) {
    auto index = this->_hashFunction(value, this->_capacity);
    while (not _table[index]) {
        index++;
    }
    _table[index] = value;
}
