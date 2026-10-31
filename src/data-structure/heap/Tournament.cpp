//
// Created by arthur on 14/08/24.
//

#include "data-structure/heap/Tournament.h"

#include <stdexcept>

namespace tournament_detail {
inline std::size_t leavesFor(std::size_t capacity) {
  std::size_t leaves = 1;
  while (leaves < capacity) {
    leaves *= 2;
  }
  return leaves;
}
} // namespace tournament_detail

template <class T>
Tournament<T>::Tournament(const std::size_t &capacity)
    : _nodes(2 * tournament_detail::leavesFor(capacity) - 1),
      _leaves(tournament_detail::leavesFor(capacity)), _capacity(capacity) {}

template <class T>
Tournament<T> Tournament<T>::from(const T *array, std::size_t n) {
  Tournament<T> tournament(n);
  for (std::size_t i = 0; i < n; i++) {
    tournament.insert(array[i]);
  }
  return tournament;
}

template <class T>
std::size_t Tournament<T>::parentOf(const std::size_t &index) const {
  return index == 0 ? 0 : (index - 1) / 2;
}

template <class T>
std::size_t Tournament<T>::rightChildOf(const std::size_t &index) const {
  return 2 * index + 2;
}

template <class T>
std::size_t Tournament<T>::leftChildOf(const std::size_t &index) const {
  return 2 * index + 1;
}

template <class T>
const std::optional<T> &Tournament<T>::winnerOf(std::size_t parent) const {
  const std::optional<T> &left = _nodes[leftChildOf(parent)];
  const std::optional<T> &right = _nodes[rightChildOf(parent)];

  // a disputa só é decidida por `>`; em caso de empate vence o da esquerda
  if (not right.has_value() or (left.has_value() and not(*right > *left))) {
    return left;
  }
  return right;
}

template <class T> void Tournament<T>::replay(std::size_t nodeIndex) {
  while (nodeIndex != 0) {
    std::size_t parent = parentOf(nodeIndex);
    _nodes[parent] = winnerOf(parent);
    nodeIndex = parent;
  }
}

template <class T> T Tournament<T>::peekRoot() const {
  if (_size == 0) {
    throw std::out_of_range("Tournament is empty, cannot peek champion.");
  }

  return *_nodes[0];
}

template <class T> T Tournament<T>::removeRoot() {
  if (_size == 0) {
    throw std::out_of_range("Tournament is empty, cannot remove champion.");
  }

  T champion = *_nodes[0];

  // desce pelo caminho do campeão até a folha que o contém
  std::size_t node = 0;
  while (node < _leaves - 1) {
    std::size_t left = leftChildOf(node);
    std::size_t right = rightChildOf(node);
    node = (&winnerOf(node) == &_nodes[left]) ? left : right;
  }

  _nodes[node].reset();
  _size--;
  if (node == 0) {
    return champion; // torneio com uma única folha
  }
  replay(node);

  return champion;
}

template <class T> void Tournament<T>::insert(const T &value) {
  if (_size == _capacity) {
    throw std::runtime_error("The tournament is full");
  }

  std::size_t leaf = _leaves - 1;
  while (_nodes[leaf].has_value()) {
    leaf++;
  }

  _nodes[leaf] = value;
  _size++;
  if (leaf != 0) {
    replay(leaf);
  }
}

template <class T> bool Tournament<T>::isFull() const {
  return _size == _capacity;
}

template <class T> bool Tournament<T>::isEmpty() const { return _size == 0; }

template <class T> std::size_t Tournament<T>::getCapacity() const {
  return _capacity;
}

template <class T> std::size_t Tournament<T>::getSize() const { return _size; }

template <class T> T &Tournament<T>::operator[](std::size_t index) const {
  if (index >= _nodes.size() or not _nodes[index].has_value()) {
    throw std::out_of_range("Index out of range");
  }

  return *_nodes[index];
}
