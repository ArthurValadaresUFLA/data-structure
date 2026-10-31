#include "data-structure/tree/binary_search_tree/DoublyLinkedBinarySearchTree.h"

#include <utility>
#include <vector>

template <class T>
void DoublyLinkedBinarySearchTree<T>::destroy(Node *root) noexcept {
  std::vector<Node *> pending;
  if (root != nullptr) {
    pending.push_back(root);
  }

  while (not pending.empty()) {
    Node *current = pending.back();
    pending.pop_back();

    if (current->getLeft() != nullptr) {
      pending.push_back(current->getLeft());
    }
    if (current->getRight() != nullptr) {
      pending.push_back(current->getRight());
    }
    delete current;
  }
}

template <class T>
DoublyLinkedBinaryTreeNodeInterface<T> *
DoublyLinkedBinarySearchTree<T>::clone(const Node *source) {
  if (source == nullptr) {
    return nullptr;
  }

  Node *root = new DoublyLinkedBinaryTreeNode<T>(source->getValue());
  try {
    std::vector<std::pair<const Node *, Node *>> pending{{source, root}};

    while (not pending.empty()) {
      auto [from, to] = pending.back();
      pending.pop_back();

      if (from->getLeft() != nullptr) {
        Node *left =
            new DoublyLinkedBinaryTreeNode<T>(from->getLeft()->getValue());
        to->setLeft(left);
        left->setParent(to);
        pending.emplace_back(from->getLeft(), left);
      }
      if (from->getRight() != nullptr) {
        Node *right =
            new DoublyLinkedBinaryTreeNode<T>(from->getRight()->getValue());
        to->setRight(right);
        right->setParent(to);
        pending.emplace_back(from->getRight(), right);
      }
    }
  } catch (...) {
    destroy(root); // tudo o que já foi ligado à raiz é liberado
    throw;
  }

  return root;
}

template <class T>
DoublyLinkedBinarySearchTree<T>::DoublyLinkedBinarySearchTree(
    const DoublyLinkedBinarySearchTree &other)
    : AbstractBinarySearchTree<T, DoublyLinkedBinaryTreeNodeInterface<T>>(
          clone(other._root)) {}

template <class T>
DoublyLinkedBinarySearchTree<T>::DoublyLinkedBinarySearchTree(
    DoublyLinkedBinarySearchTree &&other) noexcept
    : AbstractBinarySearchTree<T, DoublyLinkedBinaryTreeNodeInterface<T>>(
          nullptr) {
  swap(other);
}

template <class T>
DoublyLinkedBinarySearchTree<T> &DoublyLinkedBinarySearchTree<T>::operator=(
    DoublyLinkedBinarySearchTree other) noexcept {
  swap(other);
  return *this;
}

template <class T>
void DoublyLinkedBinarySearchTree<T>::swap(
    DoublyLinkedBinarySearchTree &other) noexcept {
  std::swap(this->_root, other._root);
}

template <class T>
DoublyLinkedBinarySearchTree<T>::~DoublyLinkedBinarySearchTree() {
  destroy(this->_root);
}

template <class T>
std::tuple<DoublyLinkedBinaryTreeNodeInterface<T> *,
           DoublyLinkedBinaryTreeNodeInterface<T> *>
DoublyLinkedBinarySearchTree<T>::_search(const T &value) const {
  Node *parent = nullptr;
  Node *current = this->_root;

  while (current != nullptr) {
    T stored = current->getValue();
    if (value < stored) {
      parent = current;
      current = current->getLeft();
    } else if (stored < value) {
      parent = current;
      current = current->getRight();
    } else {
      break;
    }
  }

  return std::make_tuple(parent, current);
}

template <class T>
void DoublyLinkedBinarySearchTree<T>::replaceChild(Node *parent, Node *oldChild,
                                                   Node *newChild) {
  if (parent == nullptr) {
    this->_root = newChild;
  } else if (parent->getLeft() == oldChild) {
    parent->setLeft(newChild);
  } else {
    parent->setRight(newChild);
  }
  if (newChild != nullptr) {
    newChild->setParent(parent);
  }
}

template <class T>
void DoublyLinkedBinarySearchTree<T>::insert(const T &value) {
  Node *node = new DoublyLinkedBinaryTreeNode<T>(value);

  Node *parent = nullptr;
  Node *current = this->_root;
  while (current != nullptr) {
    parent = current;
    current =
        value < current->getValue() ? current->getLeft() : current->getRight();
  }

  node->setParent(parent);
  if (parent == nullptr) {
    this->_root = node;
  } else if (value < parent->getValue()) {
    parent->setLeft(node);
  } else {
    parent->setRight(node);
  }
}

template <class T>
void DoublyLinkedBinarySearchTree<T>::remove(const T &value) {
  auto [parent, node] = _search(value);
  if (node == nullptr) {
    return;
  }

  if (node->getLeft() == nullptr) {
    replaceChild(parent, node, node->getRight());
  } else if (node->getRight() == nullptr) {
    replaceChild(parent, node, node->getLeft());
  } else {
    // dois filhos: o sucessor (mínimo da subárvore direita) ocupa o lugar
    Node *successorParent = node;
    Node *successor = node->getRight();
    while (successor->getLeft() != nullptr) {
      successorParent = successor;
      successor = successor->getLeft();
    }

    if (successorParent != node) {
      successorParent->setLeft(successor->getRight());
      if (successor->getRight() != nullptr) {
        successor->getRight()->setParent(successorParent);
      }
      successor->setRight(node->getRight());
      node->getRight()->setParent(successor);
    }
    successor->setLeft(node->getLeft());
    node->getLeft()->setParent(successor);
    replaceChild(parent, node, successor);
  }

  delete node;
}

template <class T>
const DoublyLinkedBinaryTreeNodeInterface<T> *
DoublyLinkedBinarySearchTree<T>::search(const T &value) const {
  return std::get<1>(_search(value));
}
