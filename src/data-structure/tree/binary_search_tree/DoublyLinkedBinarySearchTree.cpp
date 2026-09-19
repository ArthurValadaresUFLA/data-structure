//
// Created by arthur on 06/08/24.
//

#include "data-structure/tree/binary_search_tree/DoublyLinkedBinarySearchTree.h"

#include "tuple"

#include "data-structure/stack/LinkedStack.h"
#include "data-structure/tree/node/DoublyLinkedBinaryTreeNode.h"

template <class T>
DoublyLinkedBinaryTreeNodeInterface<T> *
DoublyLinkedBinarySearchTree<T>::treeMinimum(
    const DoublyLinkedBinaryTreeNodeInterface<T> &node) {
  SinglyLinkedBinaryTreeNodeInterface<T> *parent = nullptr;
  auto current = node;
  while (current.getLeft() != nullptr) {
    parent = nullptr;
    current = current.getLeft();
  }
  return std::tuple(parent, current);
}

template <class T>
DoublyLinkedBinaryTreeNodeInterface<T> *
DoublyLinkedBinarySearchTree<T>::_search(const T &value) const {
  SinglyLinkedBinaryTreeNodeInterface<T> *parent = nullptr;
  auto current = this->_root;
  while (current != nullptr and value != current->getValue()) {
    parent = current;
    if (value < current->getValue()) {
      current = current->getLeft();
    } else {
      current = current->getRight();
    }
  }
  return std::make_tuple(parent, current);
}

template <class T>
void DoublyLinkedBinarySearchTree<T>::transplant(
    DoublyLinkedBinaryTreeNodeInterface<T> *rootOn,
    DoublyLinkedBinaryTreeNodeInterface<T> *subtree) {
  if (rootOn->getParent() == nullptr) {
    this->_root = rootOn;
  } else if (rootOn == rootOn->getParent()->getLeft()) {
    rootOn->getParent()->setLeft(subtree);
  } else {
    rootOn->getParent()->setRight(subtree);
  }
  if (subtree != nullptr) {
    subtree->setParent() = rootOn->getParent();
  }
}

template <class T>
DoublyLinkedBinarySearchTree<T>::~DoublyLinkedBinarySearchTree() {
  auto stack = LinkedStack<DoublyLinkedBinaryTreeNodeInterface<T> *>();

  stack.stackUp(this->_root);
  DoublyLinkedBinaryTreeNodeInterface<T> *parent = nullptr;
  DoublyLinkedBinaryTreeNodeInterface<T> *current;
  while (not stack.empty()) {
    current = stack.unstack();
    auto left = current->getLeft();
    auto right = current->getRight();
    if (left != nullptr) {
      stack.stackUp(left);
      parent = current;
    } else if (right != nullptr) {
      stack.stackUp(right);
      parent = current;
    } else {
      if (parent->getRight() == current) {
        parent->setRight(nullptr);
      }

      if (parent->getLeft() == current) {
        parent->setLeft(nullptr);
      }

      delete current;
    }
  }
}

template <class T>
void DoublyLinkedBinarySearchTree<T>::insert(const T &value) {
  DoublyLinkedBinaryTreeNodeInterface<T> *node =
      new DoublyLinkedBinaryTreeNode(value);

  DoublyLinkedBinaryTreeNodeInterface<T> *parent = nullptr;
  auto current = this->_root;

  if (current == nullptr) {
    this->_root = node;
    return;
  }

  while (current != nullptr) {
    parent = current;
    if (value < current->getValue()) {
      current = current->getLeft();
    } else {
      current = current->getRight();
    }
  }

  if (value < parent->getValue()) {
    parent->setLeft(node);
  } else {
    parent->setRight(node);
  }
}

template <class T>
void DoublyLinkedBinarySearchTree<T>::remove(const T &value) {
  auto [parent, node] = _search(value);
  if (node->getLeft() == nullptr) {
    transplant(node, parent, node->getRight());
  } else if (node->getRight() == nullptr) {
    transplant(node, parent, node->getLeft());
  } else {
    auto [p, y] = treeMinimum(node->getRight());
    if (p != node) {
      transplant(y, y->getRight());
      y->setRight(node->getRight());
    }
    transplant(node, parent, y);
    y->setLeft(node->getLeft());
    y->getLeft()->setParent(y);
  }
}

template <class T>
const DoublyLinkedBinaryTreeNodeInterface<T> *
DoublyLinkedBinarySearchTree<T>::search(const T &value) const {
  const auto result = _search(value);
  return result;
}
