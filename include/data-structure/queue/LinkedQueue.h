//
// Created by arthur on 20/06/24.
//

#ifndef DATA_STRUCTURE_LINKEDQUEUE_H
#define DATA_STRUCTURE_LINKEDQUEUE_H

#include "data-structure/node/DoublyLinkedNode.h"
#include "data-structure/queue/AbstractLinkedQueue.h"
#include "data-structure/queue/interface/QueueInterface.h"

/**
 * @class LinkedQueue
 * @brief Uma classe que representa uma implementação de fila vinculada
 * @tparam T O tipo de dados armazenados na fila
 *
 * Esta classe fornece uma implementação básica de uma fila vinculada usando nós
 * duplamente vinculados. É uma classe abstrata destinado a ser herdado por
 * outras classes que implementam estruturas de dados de fila específicas.
 *
 * @see AbstractLinkedQueue, QueueInterface, DoublyLinkedNodeInterface,
 * AbstractNode
 */
template <class T>
class LinkedQueue : AbstractLinkedQueue<T>, QueueInterface<T> {
 private:
  /**
   * @class LinkedQueue
   * @brief Uma classe que representa uma implementação de uma fila vinculada
   * @tparam T O tipo de dados armazenados na fila
   *
   * Esta classe fornece uma implementação básica de uma fila vinculada usando
   * nós duplamente vinculados. É uma classe abstrata destinado a ser herdado
   * por outras classes que implementam estruturas de dados de fila específicas.
   *
   * @see AbstractLinkedQueue, QueueInterface, DoublyLinkedNodeInterface,
   * AbstractNode
   */
  LinkedQueue(DoublyLinkedNode<T>* begin, DoublyLinkedNode<T>* end)
      : AbstractLinkedQueue<T>(begin, end) {}

 public:
 private:
  /**
   * @brief Adiciona um elemento ao final da fila
   *
   * Esta função adiciona um elemento ao final da fila.
   * Se a fila estiver vazia, o elemento se torna o
   * início e fim da fila. Caso contrário, o elemento
   * é inserido após o final atual da fila.
   *
   * @param data O elemento a ser adicionado à fila
   * @tparam T O tipo de dados a serem armazenados na fila
   *
   * @see dequeue(), size(), isEmpty(), peek()
   */
  void queue(T data) override;

  /**
   * @brief Remove e retorna o elemento no início da fila.
   *
   * Esta função remove e retorna o elemento no início da fila. Se a fila
   * estiver vazia, nullptr será retornado.
   *
   * @tparam T O tipo de dados armazenados na fila.
   * @return O elemento no início da fila ou nullptr se a fila estiver vazia.
   */
  T dequeue() override;

  /**
   * @brief Obtenha o tamanho do LinkedQueue.
   *
   * Esta função retorna o número de elementos no LinkedQueue.
   *
   * @return O tamanho do LinkedQueue como um valor size_t.
   */
  [[nodiscard]] size_t size() const override;

  /**
   * @brief Verifica se a fila vinculada está vazia.
   *
   * @return true se a fila vinculada estiver vazia; caso contrário, false.
   */
  [[nodiscard]] bool isEmpty() const override;

  /**
   * Retorna o elemento no início da fila sem removê-lo.
   *
   * @tparam T O tipo de dados armazenados na fila.
   * @return O elemento no início da fila.
   *
   * @see LinkedQueue::dequeue(), LinkedQueue::isEmpty()
   */
  T peek() const override;
};

#endif  // DATA_STRUCTURE_LINKEDQUEUE_H
