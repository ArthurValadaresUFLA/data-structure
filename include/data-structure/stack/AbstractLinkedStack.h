//
// Created by arthur on 22/06/24.
//

#ifndef DATA_STRUCTURE_ABSTRACTLINKEDSTACK_H
#define DATA_STRUCTURE_ABSTRACTLINKEDSTACK_H

#include <cstddef>

#include "data-structure/node/interface/SinglyLinkedNodeInterface.h"

/**
 * @class AbstractLinkedStack
 * @brief Representa uma pilha vinculada abstrata.
 *
 * Esta classe é uma classe modelo que representa uma pilha vinculada abstrata.
 * Fornece funcionalidade básica para manipular uma pilha usando uma estrutura
 * simplesmente encadeada: cada nó aponta para o nó imediatamente abaixo dele.
 *
 * @tparam T O tipo de dados a serem armazenados na pilha.
 */
template <class T> class AbstractLinkedStack {
protected:
  /// Nó do topo da pilha (nullptr quando a pilha está vazia)
  SinglyLinkedNodeInterface<T> *_top = nullptr;

  /// Quantidade de elementos empilhados
  std::size_t _size = 0;

  /// Construtor protegido
  /// @param top nó do topo (nullptr para uma pilha vazia)
  explicit AbstractLinkedStack(SinglyLinkedNodeInterface<T> *top) : _top(top) {}
};

#endif // DATA_STRUCTURE_ABSTRACTLINKEDSTACK_H
