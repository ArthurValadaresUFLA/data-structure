#include "data-structure/tree/node/DoublyLinkedBinaryTreeNode.h"

template <class T>
DoublyLinkedBinaryTreeNodeInterface<T> *
DoublyLinkedBinaryTreeNode<T>::getRight() const {
  return this->_right;
}

template <class T>
void DoublyLinkedBinaryTreeNode<T>::setRight(
    DoublyLinkedBinaryTreeNodeInterface<T> *right) {
  this->_right = right;
}

template <class T>
DoublyLinkedBinaryTreeNodeInterface<T> *
DoublyLinkedBinaryTreeNode<T>::getLeft() const {
  return this->_left;
}

template <class T>
void DoublyLinkedBinaryTreeNode<T>::setLeft(
    DoublyLinkedBinaryTreeNodeInterface<T> *left) {
  this->_left = left;
}

template <class T> T DoublyLinkedBinaryTreeNode<T>::getValue() const {
  return this->_value;
}

template <class T> void DoublyLinkedBinaryTreeNode<T>::setValue(T value) {
  this->_value = value;
}

template <class T> int DoublyLinkedBinaryTreeNode<T>::childCount() const {
  int count = 0;

  if (this->getRight() != nullptr) {
    count++;
  }

  if (this->getLeft() != nullptr) {
    count++;
  }

  return count;
}

template <class T>
DoublyLinkedBinaryTreeNodeInterface<T> *
DoublyLinkedBinaryTreeNode<T>::getParent() const {
  return this->_parent;
}

template <class T>
void DoublyLinkedBinaryTreeNode<T>::setParent(
    DoublyLinkedBinaryTreeNodeInterface<T> *parent) {
  this->_parent = parent;
}
