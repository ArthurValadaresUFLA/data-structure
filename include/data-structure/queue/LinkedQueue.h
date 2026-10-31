//
// Created by arthur on 20/06/24.
//

#ifndef DATA_STRUCTURE_LINKEDQUEUE_H
#define DATA_STRUCTURE_LINKEDQUEUE_H

#include <cstddef>

#include "data-structure/node/SinglyLinkedNode.h"
#include "data-structure/queue/AbstractLinkedQueue.h"
#include "data-structure/queue/interface/QueueInterface.h"

/**
 * @class LinkedQueue
 * @brief Fila encadeada de capacidade ilimitada.
 *
 * A fila é dona dos nós, alocados dinamicamente a cada enfileiramento e
 * liberados a cada desenfileiramento e no destrutor. Todas as operações são
 * O(1). A cópia é profunda; a movimentação transfere a posse dos nós.
 *
 * @tparam T O tipo de dados armazenados na fila
 */
template <class T>
class LinkedQueue : AbstractLinkedQueue<T>, public QueueInterface<T> {
public:
  /// Cria uma fila vazia
  LinkedQueue() : AbstractLinkedQueue<T>(nullptr, nullptr) {}

  /// Construtor de cópia profunda
  LinkedQueue(const LinkedQueue &other);

  /// Construtor de movimentação: a fila de origem fica vazia
  LinkedQueue(LinkedQueue &&other) noexcept;

  /// Atribuição por cópia ou movimentação (copy-and-swap)
  LinkedQueue &operator=(LinkedQueue other) noexcept;

  /// Destrutor: libera todos os nós
  ~LinkedQueue() override;

  /// Troca o conteúdo com outra fila, em O(1)
  void swap(LinkedQueue &other) noexcept;

  /// Adiciona um elemento ao final da fila
  void queue(T data) override;

  /// Remove e retorna o elemento do início da fila
  /// @throw std::runtime_error se a fila estiver vazia
  T dequeue() override;

  /// Retorna o número de elementos na fila
  [[nodiscard]] std::size_t size() const override;

  /// Verifica se a fila está vazia
  [[nodiscard]] bool isEmpty() const override;

  /// Retorna o elemento do início da fila (o próximo a sair) sem removê-lo
  /// @throw std::runtime_error se a fila estiver vazia
  T peek() const override;
};

#include "data-structure/queue/LinkedQueue.cpp"

#endif // DATA_STRUCTURE_LINKEDQUEUE_H
