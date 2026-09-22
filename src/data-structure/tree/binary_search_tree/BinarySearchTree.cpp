#include "data-structure/tree/binary_search_tree/BinarySearchTree.h"

#include "data-structure/stack/LinkedStack.h"

template <class T>
std::tuple<SinglyLinkedBinaryTreeNodeInterface<T> *,
           SinglyLinkedBinaryTreeNodeInterface<T> *>
BinarySearchTree<T>::treeMinimum(const SinglyLinkedBinaryTreeNode<T> &node) {
  SinglyLinkedBinaryTreeNodeInterface<T> *parent = nullptr;
  auto current = node;
  while (current.getLeft() != nullptr) {
    parent = nullptr;
    current = current.getLeft();
  }
  return std::tuple(parent, current);
}

template <class T>
std::tuple<SinglyLinkedBinaryTreeNodeInterface<T> *,
           SinglyLinkedBinaryTreeNodeInterface<T> *>
BinarySearchTree<T>::_search(const T &value) const {
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
void BinarySearchTree<T>::transplant(
    SinglyLinkedBinaryTreeNodeInterface<T> *rootOn,
    SinglyLinkedBinaryTreeNodeInterface<T> *rootOnParent,
    SinglyLinkedBinaryTreeNodeInterface<T> *subtree) {
  if (rootOnParent == nullptr) {
    this->_root = rootOn;
  } else if (rootOn == rootOnParent->getLeft()) {
    rootOnParent->setLeft(subtree);
  } else {
    rootOnParent->setRight(subtree);
  }
}

template <class T> BinarySearchTree<T>::~BinarySearchTree() {
  auto stack = LinkedStack<SinglyLinkedBinaryTreeNode<T> *>();

  stack.stackUp(this->_root);
  SinglyLinkedBinaryTreeNode<T> *parent = nullptr;
  SinglyLinkedBinaryTreeNode<T> *current;
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

template <class T> void BinarySearchTree<T>::insert(const T &value) {
  SinglyLinkedBinaryTreeNode<T> *node = new SinglyLinkedBinaryTreeNode(value);

  SinglyLinkedBinaryTreeNode<T> *parent = nullptr;
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

template <class T> void BinarySearchTree<T>::remove(const T &value) {
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
  }
}

template <class T>
const SinglyLinkedBinaryTreeNodeInterface<T> *
BinarySearchTree<T>::search(const T &value) const {
  const auto result = _search(value);
  return result;
}
