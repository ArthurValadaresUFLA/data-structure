//
// Created by arthur on 29/07/24.
//

#ifndef DATA_STRUCTURE_SINGLYLINKEDBINARYTREENODE_H
#define DATA_STRUCTURE_SINGLYLINKEDBINARYTREENODE_H

#include "data-structure/tree/node/AbstractSinglyLinkedBinaryTreeNode.h"
#include "data-structure/tree/node/interface/SinglyLinkedBinaryTreeNodeInterface.h"

/**
 * @class SinglyLinkedBinaryTreeNode
 * @brief Um nó em uma árvore binária vinculada individualmente.
 *
 * Esta classe representa um nó em uma árvore binária vinculada individualmente,
 * que pode ter um filho esquerdo e um filho direito.
 *
 * @tparam T O tipo de valor armazenado no nó.
 */
template <class T>
class SinglyLinkedBinaryTreeNode
    : AbstractSinglyLinkedBinaryTreeNode<T>,
      public SinglyLinkedBinaryTreeNodeInterface<T> {
public:
  /**
   * @brief Constrói um nó com um valor e dois filhos.
   *
   * @param value O valor a ser armazenado no nó.
   * @param right Um ponteiro para o nó filho certo.
   * @param left Um ponteiro para o nó filho esquerdo.
   */
  SinglyLinkedBinaryTreeNode(T value,
                             SinglyLinkedBinaryTreeNodeInterface<T> *right,
                             SinglyLinkedBinaryTreeNodeInterface<T> *left)
      : AbstractSinglyLinkedBinaryTreeNode<T>(value, right, left) {}

  /**
   * @brief Constrói um nó com um valor e um filho certo.
   *
   * @param value O valor a ser armazenado no nó.
   * @param right Um ponteiro para o nó filho certo.
   */
  SinglyLinkedBinaryTreeNode(T value,
                             SinglyLinkedBinaryTreeNodeInterface<T> *right)
      : AbstractSinglyLinkedBinaryTreeNode<T>(value, right) {}

  /**
   * @brief Constrói um nó com um valor e sem filhos.
   *
   * @param value O valor a ser armazenado no nó.
   */
  explicit SinglyLinkedBinaryTreeNode(T value)
      : AbstractSinglyLinkedBinaryTreeNode<T>(value) {}

  /**
   * @brief Obtém o filho certo do nó.
   *
   * @return Um ponteiro para o nó filho certo.
   */
  SinglyLinkedBinaryTreeNodeInterface<T> *getRight() const override;

  /**
   * @brief Define o filho direito do nó.
   *
   * @param right Um ponteiro para o novo nó filho direito.
   */
  void setRight(SinglyLinkedBinaryTreeNodeInterface<T> *right) override;

  /**
   * @brief Obtém o filho esquerdo do nó.
   *
   * @return Um ponteiro para o nó filho esquerdo.
   */
  SinglyLinkedBinaryTreeNodeInterface<T> *getLeft() const override;

  /**
   * @brief Define o filho esquerdo do nó.
   *
   * @param left Um ponteiro para o novo nó filho esquerdo.
   */
  void setLeft(SinglyLinkedBinaryTreeNodeInterface<T> *left) override;

  /**
   * @brief Obtém o valor armazenado no nó.
   *
   * @return O valor armazenado no nó.
   */
  T getValue() const override;

  /**
   * @brief Define o valor armazenado no nó.
   *
   * @param value O novo valor a ser armazenado no nó.
   */
  void setValue(T value) override;

  /// Retorna o número de filhos (0, 1 ou 2) do nó
  [[nodiscard]] int childCount() const override;
};

#include "data-structure/tree/node/SinglyLinkedBinaryTreeNode.cpp"

#endif // DATA_STRUCTURE_SINGLYLINKEDBINARYTREENODE_H
