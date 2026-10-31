//
// Created by arthur on 20/06/24.
//

#ifndef DATA_STRUCTURE_ARRAYQUEUE_H
#define DATA_STRUCTURE_ARRAYQUEUE_H

#include <cstddef>

#include "data-structure/queue/AbstractArrayQueue.h"
#include "data-structure/queue/interface/QueueInterface.h"

/**
 * @class ArrayQueue
 * @brief Fila de capacidade fixa implementada sobre um array circular.
 *
 * Todas as operações são O(1). Ao enfileirar com a fila cheia é lançado um
 * std::runtime_error; ao desenfileirar ou espiar uma fila vazia também.
 * Copiar uma fila copia seus elementos; mover transfere a posse do array.
 *
 * @tparam T O tipo de elementos a serem armazenados na fila
 */
template <class T>
class ArrayQueue : AbstractArrayQueue<T>, public QueueInterface<T> {
public:
  /**
   * @brief Cria uma fila vazia.
   * @param initialCapacity número máximo de elementos que a fila comporta
   */
  explicit ArrayQueue(std::size_t initialCapacity)
      : AbstractArrayQueue<T>(initialCapacity) {}

  /// Adiciona um elemento ao final da fila
  /// @throw std::runtime_error se a fila estiver cheia
  void queue(T data) override;

  /// Remove e retorna o elemento do início da fila
  /// @throw std::runtime_error se a fila estiver vazia
  T dequeue() override;

  /// Retorna o número de elementos na fila
  [[nodiscard]] std::size_t size() const override;

  /// Verifica se a fila está vazia
  [[nodiscard]] bool isEmpty() const override;

  /// Retorna o elemento do início da fila sem removê-lo
  /// @throw std::runtime_error se a fila estiver vazia
  T peek() const override;

  /// Verifica se a fila atingiu a capacidade máxima
  [[nodiscard]] bool isFull() const;

  /// Retorna a capacidade máxima da fila
  [[nodiscard]] std::size_t getCapacity() const;
};

#include "data-structure/queue/ArrayQueue.cpp"

#endif // DATA_STRUCTURE_ARRAYQUEUE_H
