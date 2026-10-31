//
// Created by arthur on 14/08/24.
//

#ifndef DATA_STRUCTURE_ABSTRACTHEAP_H
#define DATA_STRUCTURE_ABSTRACTHEAP_H

#include <algorithm>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>

#include "data-structure/heap/interface/HeapInterface.h"

/**
 * @class AbstractHeap
 * @brief Uma classe abstrata para implementar estruturas de dados heap
 * binárias armazenadas em array.
 *
 * Os elementos ficam em _data[0 .. _size - 1] com a raiz em _data[0]; os filhos
 * de i estão em 2i + 1 e 2i + 2. O array é gerenciado por std::unique_ptr<T[]>
 * (RAII), logo é liberado uma única vez com `delete[]`. A cópia é profunda e a
 * movimentação transfere a posse. As classes derivadas só precisam definir a
 * relação de ordem, passada aos métodos protegidos siftUp/siftDown.
 *
 * @tparam T O tipo de dados a serem armazenados no heap.
 */
template <class T> class AbstractHeap : public HeapInterface<T> {
protected:
  /// Armazenamento dos elementos
  std::unique_ptr<T[]> _data;

  /// Quantidade de elementos atualmente no heap
  std::size_t _size = 0;

  /// Quantidade máxima de elementos
  std::size_t _capacity;

  /**
   * @brief Construtor que aloca o armazenamento do heap.
   * @param capacity o número máximo de elementos do heap
   */
  explicit AbstractHeap(const std::size_t &capacity)
      : _data(new T[capacity]), _capacity(capacity) {}

  /// Construtor de cópia profunda: copia apenas os elementos válidos
  AbstractHeap(const AbstractHeap &other)
      : _data(new T[other._capacity]), _size(other._size),
        _capacity(other._capacity) {
    std::copy(other._data.get(), other._data.get() + other._size, _data.get());
  }

  /// Construtor de movimentação: a origem fica vazia e sem capacidade
  AbstractHeap(AbstractHeap &&other) noexcept
      : _data(std::move(other._data)), _size(other._size),
        _capacity(other._capacity) {
    other._size = 0;
    other._capacity = 0;
  }

  /// Atribuição por cópia (copy-and-swap), segura contra auto-atribuição
  AbstractHeap &operator=(const AbstractHeap &other) {
    if (this != &other) {
      // aloca e copia antes de alterar o objeto: se falhar, nada muda
      std::unique_ptr<T[]> data(new T[other._capacity]);
      std::copy(other._data.get(), other._data.get() + other._size, data.get());
      _data = std::move(data);
      _size = other._size;
      _capacity = other._capacity;
    }
    return *this;
  }

  /// Atribuição por movimentação: troca o conteúdo com a origem (que passa a
  /// guardar o antigo conteúdo deste objeto e será destruída em seguida)
  AbstractHeap &operator=(AbstractHeap &&other) noexcept {
    std::swap(_data, other._data);
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
    return *this;
  }

  /// Insere o valor na próxima posição livre e o faz subir até que a relação
  /// de ordem seja respeitada.
  /// @param value valor a inserir
  /// @param before predicado before(a, b): true se a deve ficar acima de b
  /// @throw std::runtime_error se o heap estiver cheio
  template <class Before> void pushSorted(const T &value, Before before) {
    if (_size == _capacity) {
      throw std::runtime_error("The heap is full");
    }

    std::size_t hole = _size++;
    while (hole > 0 and before(value, _data[parentOf(hole)])) {
      _data[hole] = _data[parentOf(hole)];
      hole = parentOf(hole);
    }
    _data[hole] = value;
  }

  /// Remove e retorna a raiz, movendo o último elemento para o topo e
  /// fazendo-o descer até restabelecer a relação de ordem.
  /// @param before predicado before(a, b): true se a deve ficar acima de b
  /// @throw std::out_of_range se o heap estiver vazio
  template <class Before> T popSorted(Before before) {
    if (_size == 0) {
      throw std::out_of_range("Heap is empty, cannot remove root.");
    }

    T root = _data[0];
    _size--;

    if (_size > 0) {
      _data[0] = _data[_size];

      std::size_t current = 0;
      while (true) {
        std::size_t best = current;
        std::size_t left = leftChildOf(current);
        std::size_t right = rightChildOf(current);

        if (left < _size and before(_data[left], _data[best])) {
          best = left;
        }
        if (right < _size and before(_data[right], _data[best])) {
          best = right;
        }
        if (best == current) {
          break;
        }

        std::swap(_data[current], _data[best]);
        current = best;
      }
    }

    return root;
  }

public:
  /// Índice do pai de index (a raiz é pai de si mesma)
  [[nodiscard]] std::size_t parentOf(const std::size_t &index) const override;

  /// Índice do filho direito de index (2 * index + 2)
  [[nodiscard]] std::size_t
  rightChildOf(const std::size_t &index) const override;

  /// Índice do filho esquerdo de index (2 * index + 1)
  [[nodiscard]] std::size_t
  leftChildOf(const std::size_t &index) const override;

  /// Retorna a raiz sem removê-la
  /// @throw std::out_of_range se o heap estiver vazio
  [[nodiscard]] T peekRoot() const override;

  /// Verifica se o heap atingiu a capacidade máxima
  [[nodiscard]] bool isFull() const override;

  /// Verifica se o heap está vazio
  [[nodiscard]] bool isEmpty() const override;

  /// Retorna a capacidade máxima do heap
  [[nodiscard]] std::size_t getCapacity() const override;

  /// Retorna o número de elementos no heap
  [[nodiscard]] std::size_t getSize() const override;

  /// Acessa o elemento na posição index do array do heap
  /// @throw std::out_of_range se index >= getSize()
  [[nodiscard]] T &operator[](std::size_t index) const override;

  /// Compara dois heaps: mesma capacidade, mesmo tamanho e mesmos elementos na
  /// mesma ordem
  bool operator==(const AbstractHeap &other) const;
};

#include "data-structure/heap/AbstractHeap.cpp"

#endif // DATA_STRUCTURE_ABSTRACTHEAP_H
