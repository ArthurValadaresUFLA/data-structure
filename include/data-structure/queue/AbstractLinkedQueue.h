//
// Created by arthur on 20/06/24.
//

#ifndef DATA_STRUCTURE_ABSTRACTLINKEDQUEUE_H
#define DATA_STRUCTURE_ABSTRACTLINKEDQUEUE_H

#include "data-structure/node/interface/DoublyLinkedNodeInterface.h"

/**
 * @class AbstractLinkedQueue
 * @brief Uma classe modelo que representa uma implementação abstrata de uma
 * fila vinculada
 * @tparam T O tipo de dados armazenados na fila
 *
 * Esta classe fornece uma implementação básica de uma fila vinculada usando nós
 * duplamente vinculados. É uma classe abstrata que se destina a ser herdado por
 * outras classes que implementam estruturas de dados de fila específicas.
 *
 * @see DoubleLinkedNodeInterface
 */
template <class T>
class AbstractLinkedQueue {
 protected:
  DoublyLinkedNodeInterface<T>* _begin = nullptr;
  DoublyLinkedNodeInterface<T>* _end = nullptr;

  /**
   * @brief Constrói um objeto AbstractLinkedQueue com determinados nós iniciais
   * e finais.
   * @param start O nó inicial da fila
   * @param end O nó final da fila
   */
  AbstractLinkedQueue(DoublyLinkedNodeInterface<T>* begin,
                      DoublyLinkedNodeInterface<T>* end)
      : _begin(begin), _end(end) {}
};

#endif  // DATA_STRUCTURE_ABSTRACTLINKEDQUEUE_H
