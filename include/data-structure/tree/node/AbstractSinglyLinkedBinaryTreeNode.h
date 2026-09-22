//
// Created by arthur on 29/07/24.
//

#ifndef DATA_STRUCTURE_ABSTRACTSINGLYLINKEDBINARYTREENODE_H
#define DATA_STRUCTURE_ABSTRACTSINGLYLINKEDBINARYTREENODE_H

#include "data-structure/tree/node/interface/SinglyLinkedBinaryTreeNodeInterface.h"

/**
 * @class AbstractSinglyLinkedBinaryTreeNode
 *
 * @brief A classe AbstractSinglyLinkedBinaryTreeNode representa um nó em uma
 * estrutura de árvore binária vinculada individualmente.
 *
 * Ele fornece métodos para obter e definir os nós filhos esquerdo e direito do
 * nó atual. A classe é modelada para permitir que qualquer tipo de valor seja
 * armazenado no nó.
 *
 * @tparam T O tipo do valor mantido pelo nó.
 */
template <class T> class AbstractSinglyLinkedBinaryTreeNode {
protected:
  T _value;

  SinglyLinkedBinaryTreeNodeInterface<T> *_right = nullptr;
  SinglyLinkedBinaryTreeNodeInterface<T> *_left = nullptr;

  /**
   * @brief Construtor para a classe AbstractSinglyLinkedBinaryTreeNode.
   *
   * Este construtor cria uma nova instância da classe
   * AbstractSinglyLinkedBinaryTreeNode com o valor especificado, nó filho
   * direito e nó filho esquerdo.
   *
   * @param value O valor a ser armazenado no nó.
   * @param right Um ponteiro para o nó filho certo.
   * @param left Um ponteiro para o nó filho esquerdo.
   */
  AbstractSinglyLinkedBinaryTreeNode(
      T value, SinglyLinkedBinaryTreeNodeInterface<T> *right,
      SinglyLinkedBinaryTreeNodeInterface<T> *left)
      : _value(value), _right(right), _left(left) {}

  /**
   * @brief Cria um novo objeto AbstractSinglyLinkedBinaryTreeNode com um valor
   * especificado e filho certo.
   *
   * @tparam T O tipo de valor mantido pelo nó.
   * @param value O valor a ser armazenado no nó.
   * @param right O filho certo do nó.
   */
  AbstractSinglyLinkedBinaryTreeNode(
      T value, SinglyLinkedBinaryTreeNodeInterface<T> *right)
      : _value(value), _right(right) {}

  /**
   * @brief Variável membro representando o valor armazenado no nó.
   *
   * @tparam T O tipo do valor armazenado no nó.
   */
  explicit AbstractSinglyLinkedBinaryTreeNode(T value) : _value(value) {}
};

#endif // DATA_STRUCTURE_ABSTRACTSINGLYLINKEDBINARYTREENODE_H
