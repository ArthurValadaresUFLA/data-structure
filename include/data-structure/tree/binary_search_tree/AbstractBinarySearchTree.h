//
// Created by arthur on 06/08/24.
//

#ifndef DATA_STRUCTURE_ABSTRACTBINARYSEARCHTREE_H
#define DATA_STRUCTURE_ABSTRACTBINARYSEARCHTREE_H

#include "data-structure/tree/node/interface/DoublyLinkedBinaryTreeNodeInterface.h"
#include "data-structure/tree/node/interface/SinglyLinkedBinaryTreeNodeInterface.h"

/// @brief Classe abstrata que guarda a raiz de uma árvore binária de busca.
///
/// A árvore é dona de todos os nós alcançáveis a partir da raiz.
/// @tparam T tipo dos valores armazenados
/// @tparam Node interface dos nós usados pela árvore
template <class T, class Node = SinglyLinkedBinaryTreeNodeInterface<T>>
class AbstractBinarySearchTree {
protected:
  /// Raiz da árvore (nullptr se estiver vazia)
  Node *_root = nullptr;

  /// Construtor protegido
  /// @param root raiz inicial
  explicit AbstractBinarySearchTree(Node *root) : _root(root) {}
};

#endif // DATA_STRUCTURE_ABSTRACTBINARYSEARCHTREE_H
