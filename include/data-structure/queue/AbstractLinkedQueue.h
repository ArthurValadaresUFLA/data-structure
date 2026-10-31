//
// Created by arthur on 20/06/24.
//

#ifndef DATA_STRUCTURE_ABSTRACTLINKEDQUEUE_H
#define DATA_STRUCTURE_ABSTRACTLINKEDQUEUE_H

#include <cstddef>

#include "data-structure/node/interface/SinglyLinkedNodeInterface.h"

/**
 * @class AbstractLinkedQueue
 * @brief Uma classe modelo que representa uma implementação abstrata de uma
 * fila vinculada
 * @tparam T O tipo de dados armazenados na fila
 *
 * A fila é uma estrutura simplesmente encadeada: cada nó aponta para o nó que
 * está logo atrás dele na fila. A inserção ocorre no fim (_end) e a remoção no
 * início (_begin), ambas em O(1).
 *
 * @see SinglyLinkedNodeInterface
 */
template <class T> class AbstractLinkedQueue {
protected:
  /// Primeiro nó da fila (próximo a sair)
  SinglyLinkedNodeInterface<T> *_begin = nullptr;

  /// Último nó da fila (último a entrar)
  SinglyLinkedNodeInterface<T> *_end = nullptr;

  /// Quantidade de elementos
  std::size_t _size = 0;

  /**
   * @brief Constrói um objeto AbstractLinkedQueue com determinados nós iniciais
   * e finais.
   * @param begin O nó inicial da fila
   * @param end O nó final da fila
   */
  AbstractLinkedQueue(SinglyLinkedNodeInterface<T> *begin,
                      SinglyLinkedNodeInterface<T> *end)
      : _begin(begin), _end(end) {}
};

#endif // DATA_STRUCTURE_ABSTRACTLINKEDQUEUE_H
