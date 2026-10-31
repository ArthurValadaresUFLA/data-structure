//
// Created by arthur on 22/06/24.
//

#ifndef DATA_STRUCTURE_ABSTRACTARRAYSTACK_H
#define DATA_STRUCTURE_ABSTRACTARRAYSTACK_H

#include <algorithm>
#include <cstddef>
#include <memory>
#include <utility>

/// @brief Classe abstrata que concentra o armazenamento de uma pilha em array.
///
/// O array é gerenciado por um std::unique_ptr<T[]> (RAII): não há `delete`
/// manual, a memória é liberada exatamente uma vez e `delete[]` é usado
/// automaticamente. A cópia é profunda e a movimentação transfere a posse.
/// @tparam T O tipo de elementos armazenados na pilha.
template <class T> class AbstractArrayStack {
protected:
  /// Array que armazena os elementos; o elemento do topo está em
  /// _array[_size - 1]
  std::unique_ptr<T[]> _array;

  /// Quantidade de elementos atualmente empilhados
  std::size_t _size = 0;

  /// Quantidade máxima de elementos que a pilha comporta
  std::size_t _capacity = 0;

  /// Construtor que aloca o armazenamento
  /// @param capacity capacidade máxima da pilha
  explicit AbstractArrayStack(std::size_t capacity)
      : _array(new T[capacity]), _capacity(capacity) {}

  /// Construtor de cópia profunda: copia apenas os elementos válidos
  AbstractArrayStack(const AbstractArrayStack &source)
      : _array(new T[source._capacity]), _size(source._size),
        _capacity(source._capacity) {
    std::copy(source._array.get(), source._array.get() + source._size,
              this->_array.get());
  }

  /// Construtor de movimentação: a origem fica vazia e sem capacidade
  AbstractArrayStack(AbstractArrayStack &&source) noexcept
      : _array(std::move(source._array)), _size(source._size),
        _capacity(source._capacity) {
    source._size = 0;
    source._capacity = 0;
  }

  /// Atribuição por cópia (copy-and-swap): é segura contra auto-atribuição e
  /// mantém o objeto intacto se a alocação falhar
  AbstractArrayStack &operator=(const AbstractArrayStack &source) {
    AbstractArrayStack copy(source);
    swapWith(copy);
    return *this;
  }

  /// Atribuição por movimentação: a origem fica vazia
  AbstractArrayStack &operator=(AbstractArrayStack &&source) noexcept {
    AbstractArrayStack moved(std::move(source));
    swapWith(moved);
    return *this;
  }

  void swapWith(AbstractArrayStack &other) noexcept {
    std::swap(this->_array, other._array);
    std::swap(this->_size, other._size);
    std::swap(this->_capacity, other._capacity);
  }

  ~AbstractArrayStack() = default;
};

#endif // DATA_STRUCTURE_ABSTRACTARRAYSTACK_H
