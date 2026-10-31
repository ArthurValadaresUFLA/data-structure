//
// Created by arthur on 20/06/24.
//

#ifndef DATA_STRUCTURE_ABSTRACTARRAYQUEUE_H
#define DATA_STRUCTURE_ABSTRACTARRAYQUEUE_H

#include <algorithm>
#include <cstddef>
#include <memory>
#include <utility>

/**
 * @class AbstractArrayQueue
 * @brief Armazenamento circular de uma fila em array.
 *
 * Os elementos ocupam _array[(_head + i) % _capacity], com 0 <= i < _size. O
 * array é gerenciado por std::unique_ptr<T[]> (RAII), portanto é liberado
 * exatamente uma vez com `delete[]`. A cópia é profunda e a movimentação
 * transfere a posse.
 *
 * @tparam T O tipo de dados armazenados na fila
 */
template <class T> class AbstractArrayQueue {
protected:
  /// Armazenamento circular dos elementos
  std::unique_ptr<T[]> _array;

  /// Capacidade máxima da fila
  std::size_t _capacity = 0;

  /// Índice do primeiro elemento da fila
  std::size_t _head = 0;

  /// Quantidade de elementos na fila
  std::size_t _size = 0;

  /// Constrói o armazenamento
  /// @param initialCapacity número máximo de elementos da fila
  explicit AbstractArrayQueue(std::size_t initialCapacity)
      : _array(new T[initialCapacity]), _capacity(initialCapacity) {}

  /// Construtor de cópia profunda; o conteúdo é reorganizado a partir do
  /// índice zero
  AbstractArrayQueue(const AbstractArrayQueue &other)
      : _array(new T[other._capacity]), _capacity(other._capacity), _head(0),
        _size(other._size) {
    for (std::size_t i = 0; i < other._size; i++) {
      _array[i] = other._array[(other._head + i) % other._capacity];
    }
  }

  /// Construtor de movimentação: a origem fica vazia e sem capacidade
  AbstractArrayQueue(AbstractArrayQueue &&other) noexcept
      : _array(std::move(other._array)), _capacity(other._capacity),
        _head(other._head), _size(other._size) {
    other._capacity = 0;
    other._head = 0;
    other._size = 0;
  }

  /// Atribuição por cópia (copy-and-swap), segura contra auto-atribuição
  AbstractArrayQueue &operator=(const AbstractArrayQueue &other) {
    AbstractArrayQueue copy(other);
    swapWith(copy);
    return *this;
  }

  /// Atribuição por movimentação: a origem fica vazia
  AbstractArrayQueue &operator=(AbstractArrayQueue &&other) noexcept {
    AbstractArrayQueue moved(std::move(other));
    swapWith(moved);
    return *this;
  }

  void swapWith(AbstractArrayQueue &other) noexcept {
    std::swap(_array, other._array);
    std::swap(_capacity, other._capacity);
    std::swap(_head, other._head);
    std::swap(_size, other._size);
  }

  ~AbstractArrayQueue() = default;
};

#endif // DATA_STRUCTURE_ABSTRACTARRAYQUEUE_H
