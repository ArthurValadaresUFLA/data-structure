//
// Created by arthur on 29/07/24.
//

#ifndef DATA_STRUCTURE_ABSTRACTBINARYSEARCHTREE_H
#define DATA_STRUCTURE_ABSTRACTBINARYSEARCHTREE_H

#include "data-structure/tree/node/interface/SinglyLinkedBinaryTreeNodeInterface.h"

/**
 * @class AbstractBinarySearchTree
 * @brief Representa uma árvore de pesquisa binária abstrata.
 *
 * A classe AbstractBinarySearchTree fornece uma implementação básica de uma
 * árvore de pesquisa binária. Inclui uma variável de membro protegida _root que
 * aponta para o nó raiz da árvore.
 *
 * @tparam T O tipo de valor armazenado na árvore.
 */
template <class T> class AbstractBinarySearchTree {
protected:
  SinglyLinkedBinaryTreeNodeInterface<T> *_root = nullptr;

  explicit AbstractBinarySearchTree(
      SinglyLinkedBinaryTreeNodeInterface<T> *root)
      : _root(root) {}
};

#endif // DATA_STRUCTURE_ABSTRACTBINARYSEARCHTREE_H
