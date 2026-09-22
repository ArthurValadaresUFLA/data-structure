//
// Created by arthur on 22/06/24.
//

#ifndef DATA_STRUCTURE_ABSTRACTLINKEDSTACK_H
#define DATA_STRUCTURE_ABSTRACTLINKEDSTACK_H

#include "data-structure/node/interface/DoublyLinkedNodeInterface.h"

/**
 * @class AbstractLinkedStack
 * @brief Representa uma pilha vinculada abstrata.
 *
 * Esta classe é uma classe modelo que representa uma pilha vinculada abstrata.
 * Fornece funcionalidade básica para manipular uma pilha usando uma estrutura
 * duplamente vinculada.
 *
 * @tparam T O tipo de dados a serem armazenados na pilha.
 */
template <class T> class AbstractLinkedStack {
protected:
  DoublyLinkedNodeInterface<T> *_end = nullptr;

  explicit AbstractLinkedStack(DoublyLinkedNodeInterface<T> *end) : _end(end) {}
};

#endif // DATA_STRUCTURE_ABSTRACTLINKEDSTACK_H
