//
// Created by arthur on 20/06/24.
//

#ifndef DATA_STRUCTURE_ARRAYQUEUE_H
#define DATA_STRUCTURE_ARRAYQUEUE_H

#include "data-structure/queue/AbstractArrayQueue.h"
#include "data-structure/queue/interface/QueueInterface.h"

/**
 * @classArrayQueue
 * @brief Uma implementação de fila usando um array.
 *
 * Esta classe fornece uma estrutura de dados de fila usando um array.
 * Suporta operações como enfileirar, desenfileirar, tamanho, isEmpty e espiar.
 *
 * @tparam T O tipo de elementos armazenados na fila.
 */
template <class T> class ArrayQueue : AbstractArrayQueue<T>, QueueInterface<T> {
public:
  /**
   * @fn ArrayQueue::ArrayQueue
   * @brief Construtor para a classe ArrayQueue.
   *
   * Este construtor inicializa o objeto ArrayQueue com a capacidade inicial
   * fornecida. Chama o construtor da classe base AbstractArrayQueue passando a
   * capacidade inicial como argumento.
   *
   * @tparam T O tipo de elementos armazenados na fila.
   * @param inicialCapacity A capacidade inicial da fila.
   */
  explicit ArrayQueue(std::size_t initialCapacity)
      : AbstractArrayQueue<T>(initialCapacity) {}

  /**
   * @classArrayQueue
   * @brief Uma implementação de uma fila usando um array.
   *
   * Esta classe fornece uma estrutura de dados de uma fila usando um array.
   * Suporta operações como enfileirar, desenfileirar, tamanho, isEmpty e
   * espiar.
   *
   * @tparam T O tipo de elementos armazenados na fila.
   */
  ~ArrayQueue();

  /**
   * @classArrayQueue
   * @brief Implementação de uma fila usando um array.
   *
   * Esta classe fornece uma estrutura de dados de uma fila usando um array.
   * Suporta operações como enfileirar, desenfileirar, tamanho, isEmpty e
   * espiar.
   *
   * @tparam T O tipo de elementos armazenados na fila.
   */
  void queue(T data) override;

  /**
   * @brief Desfila o elemento no início da fila.
   *
   * Esta função remove e retorna o elemento no início da fila.
   *
   * @tparam T O tipo de elementos armazenados na fila.
   * @return O elemento no início da fila.
   * @throws std::runtime_error Se a fila estiver vazia.
   */
  T dequeue() override;

  /**
   * @fn size
   * @brief Retorna o tamanho atual da fila.
   * @return O tamanho atual da fila.
   */
  [[nodiscard]] size_t size() const override;

  /**
   * @brief Verifica se a fila está vazia.
   *
   * Esta função verifica se a fila está vazia ou não.
   *
   * @return True se a fila estiver vazia, false caso contrário.
   */
  [[nodiscard]] bool isEmpty() const override;

  /**
   * @brief Retorna o elemento que está no início da fila sem removê-lo.
   *
   * Esta função retorna o elemento no início da fila sem removê-lo.
   * Lança uma exceção se a fila estiver vazia.
   *
   * @tparam T O tipo de elementos armazenados na fila.
   *
   * @return O elemento no início da fila.
   *
   * @throw std::out_of_range se a fila estiver vazia.
   */
  T peek() const override;
};

#endif // DATA_STRUCTURE_ARRAYQUEUE_H
