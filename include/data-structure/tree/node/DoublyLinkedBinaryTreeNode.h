//
// Created by arthur on 29/07/24.
//

#ifndef DATA_STRUCTURE_DOUBLYLINKEDBINARYTREENODE_H
#define DATA_STRUCTURE_DOUBLYLINKEDBINARYTREENODE_H

#include "data-structure/tree/node/AbstractDoublyLinkedBinaryTreeNode.h"
#include "data-structure/tree/node/interface/DoublyLinkedBinaryTreeNodeInterface.h"

/**
 * @class DoublyLinkedBinaryTreeNode
 * @brief A class representing a node in a doubly linked binary tree.
 *
 * This class provides the basic functionality for a node in a doubly linked
 * binary tree. It is a template class that uses a type parameter specifying the
 * type of value stored in the node.
 *
 * @tparam T The type of value stored in the node.
 */
template <class T>
class DoublyLinkedBinaryTreeNode
    : AbstractDoublyLinkedBinaryTreeNode<T>,
      public DoublyLinkedBinaryTreeNodeInterface<T> {
public:
  DoublyLinkedBinaryTreeNode(T value,
                             DoublyLinkedBinaryTreeNodeInterface<T> *right,
                             DoublyLinkedBinaryTreeNodeInterface<T> *left,
                             DoublyLinkedBinaryTreeNodeInterface<T> *parent)
      : AbstractDoublyLinkedBinaryTreeNode<T>(value, right, left, parent) {}

  DoublyLinkedBinaryTreeNode(T value,
                             DoublyLinkedBinaryTreeNodeInterface<T> *right,
                             DoublyLinkedBinaryTreeNodeInterface<T> *left)
      : AbstractDoublyLinkedBinaryTreeNode<T>(value, right, left) {}

  DoublyLinkedBinaryTreeNode(T value,
                             DoublyLinkedBinaryTreeNodeInterface<T> *right)
      : AbstractDoublyLinkedBinaryTreeNode<T>(value, right) {}

  explicit DoublyLinkedBinaryTreeNode(T value)
      : AbstractDoublyLinkedBinaryTreeNode<T>(value) {}

  /**
   * @brief Get the right child of the current node.
   *
   * This function returns a pointer to the right child of the current node.
   *
   * @return A pointer to the right child of the current node.
   * Returns nullptr if the current node does not have a right child.
   */
  DoublyLinkedBinaryTreeNodeInterface<T> *getRight() const override;

  /**
   * @brief Set the right child of the current node.
   *
   * This function sets the right child of the current node to the specified
   * node.
   *
   * @param right A pointer to the right child node.
   */
  void setRight(DoublyLinkedBinaryTreeNodeInterface<T> *right) override;

  /**
   * @class DoublyLinkedBinaryTreeNode
   * @brief A class representing a node in a doubly linked binary tree.
   *
   * This class provides the basic functionality for a node in a doubly linked
   * binary tree. It is a template class that uses a type parameter specifying
   * the type of value stored in the node.
   *
   * @tparam T The type of value stored in the node.
   */
  DoublyLinkedBinaryTreeNodeInterface<T> *getLeft() const override;

  /**
   * @brief Set the left child of the current node.
   *
   * This function is used to set the left child of the current node in a doubly
   * linked binary tree.
   *
   * @param left A pointer to the left child node to be set.
   */
  void setLeft(DoublyLinkedBinaryTreeNodeInterface<T> *left) override;

  /**
   * @class DoublyLinkedBinaryTreeNode
   * @brief A class representing a node in a doubly linked binary tree.
   *
   * This class provides the basic functionality for a node in a doubly linked
   * binary tree. It is a template class that uses a type parameter specifying
   * the type of value stored in the node.
   *
   * @tparam T The type of value stored in the node.
   */
  T getValue() const override;

  /**
   * @brief Sets the value of the node.
   *
   * This function sets the value of the node to the specified value.
   *
   * @tparam T The type of value stored in the node.
   * @param value The value to set.
   * @return void
   */
  void setValue(T value) override;

  /**
   * @brief Returns the number of child nodes for this node.
   *
   * This function computes and returns the number of child nodes for this node.
   * A child node is any non-null node that is attached to either the left or
   * right pointer of this node.
   *
   * @return The number of child nodes.
   */
  [[nodiscard]] int childCount() const override;

private:
  /**
   * @brief Get the parent node of the current node.
   *
   * This function returns the parent node of the current node.
   *
   * @return A pointer to the parent node of the current node.
   */
  DoublyLinkedBinaryTreeNodeInterface<T> *getParent() const override;

  /**
   * @brief Set the parent node of the current node.
   *
   * This function sets the parent node of the current node. The parent node is
   * a node that comes before the current node in the binary tree.
   *
   * @param parent A pointer to the parent node.
   */
  void setParent(DoublyLinkedBinaryTreeNodeInterface<T> *parent) override;
};

#endif // DATA_STRUCTURE_DOUBLYLINKEDBINARYTREENODE_H
