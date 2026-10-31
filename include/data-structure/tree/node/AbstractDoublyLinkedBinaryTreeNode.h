//
// Created by arthur on 29/07/24.
//

#ifndef DATA_STRUCTURE_ABSTRACTDOUBLYLINKEDBINARYTREENODE_H
#define DATA_STRUCTURE_ABSTRACTDOUBLYLINKEDBINARYTREENODE_H

#include "data-structure/tree/node/interface/DoublyLinkedBinaryTreeNodeInterface.h"

/**
 * @class AbstractDoublyLinkedBinaryTreeNode
 * @brief Uma classe base abstrata para um nó de árvore binária duplamente
 * vinculado.
 *
 * Esta classe fornece a funcionalidade básica para um nó de árvore binária
 * duplamente vinculado. É uma classe de modelo que usa um parâmetro de tipo que
 * especifica o tipo de valor armazenado no nó.
 */
template <class T> class AbstractDoublyLinkedBinaryTreeNode {
protected:
  DoublyLinkedBinaryTreeNodeInterface<T> *_parent = nullptr;

  T _value;

  DoublyLinkedBinaryTreeNodeInterface<T> *_right = nullptr;
  DoublyLinkedBinaryTreeNodeInterface<T> *_left = nullptr;

  AbstractDoublyLinkedBinaryTreeNode(
      T value, DoublyLinkedBinaryTreeNodeInterface<T> *right,
      DoublyLinkedBinaryTreeNodeInterface<T> *left,
      DoublyLinkedBinaryTreeNodeInterface<T> *parent)
      : _parent(parent), _value(value), _right(right), _left(left) {}

  /**
   * @brief Constrói um objeto AbstractDoublyLinkedBinaryTreeNode com o valor
   * fornecido, filho direito e filho esquerdo.
   *
   * @param value O valor a ser armazenado no nó.
   * @param right Um ponteiro para o filho direito do nó.
   * @param left Um ponteiro para o filho esquerdo do nó.
   */
  AbstractDoublyLinkedBinaryTreeNode(
      T value, DoublyLinkedBinaryTreeNodeInterface<T> *right,
      DoublyLinkedBinaryTreeNodeInterface<T> *left)
      : _value(value), _right(right), _left(left) {}

  /**
   * @brief Constrói uma instância da classe
   * `AbstractDoublyLinkedBinaryTreeNode`.
   * @param value O valor a ser armazenado no nó.
   * @param right Um ponteiro para o nó filho certo.
   */
  AbstractDoublyLinkedBinaryTreeNode(
      T value, DoublyLinkedBinaryTreeNodeInterface<T> *right)
      : _value(value), _right(right) {}

  /**
   * @brief Constrói uma instância da classe
   * `AbstractDoublyLinkedBinaryTreeNode` com o valor fornecido.
   *
   * Este construtor recebe um valor como parâmetro e o atribui à variável
   * membro `_value`.
   *
   * @param value O valor a ser armazenado no nó.
   */
  explicit AbstractDoublyLinkedBinaryTreeNode(T value) : _value(value) {}
};

#endif // DATA_STRUCTURE_ABSTRACTDOUBLYLINKEDBINARYTREENODE_H
