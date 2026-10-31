//
// Created by arthur on 06/08/24.
//

#ifndef DATA_STRUCTURE_DOUBLYLINKEDBINARYSEARCHTREE_H
#define DATA_STRUCTURE_DOUBLYLINKEDBINARYSEARCHTREE_H

#include <tuple>

#include "data-structure/tree/binary_search_tree/AbstractBinarySearchTree.h"
#include "data-structure/tree/binary_search_tree/interface/DoublyLinkedBinarySearchTreeInterface.h"
#include "data-structure/tree/node/DoublyLinkedBinaryTreeNode.h"

/**
 * @brief Árvore binária de busca com nós duplamente ligados (cada nó conhece o
 * pai).
 *
 * A ordem usa apenas o operador `<` de T. Valores iguais são inseridos na
 * subárvore direita. A árvore é dona dos nós: o destrutor, remove, a cópia
 * (profunda) e a atribuição os gerenciam sem vazamentos nem liberação dupla. As
 * travessias são iterativas, então árvores degeneradas (muito profundas) não
 * estouram a pilha de chamadas.
 *
 * @tparam T tipo dos valores (construível por cópia, comparável com `<`)
 */
template <class T>
class DoublyLinkedBinarySearchTree
    : AbstractBinarySearchTree<T, DoublyLinkedBinaryTreeNodeInterface<T>>,
      public DoublyLinkedBinarySearchTreeInterface<T> {
private:
  using Node = DoublyLinkedBinaryTreeNodeInterface<T>;

  /// Procura o valor; retorna (pai, nó), com nó == nullptr se ausente
  [[nodiscard]] std::tuple<Node *, Node *> _search(const T &value) const;

  /// Troca, no pai, o filho oldChild por newChild (ou a raiz, se não há pai)
  void replaceChild(Node *parent, Node *oldChild, Node *newChild);

  /// Libera, sem recursão, todos os nós da subárvore
  static void destroy(Node *root) noexcept;

  /// Copia a subárvore de forma profunda
  static Node *clone(const Node *source);

public:
  /// Cria uma árvore vazia
  DoublyLinkedBinarySearchTree()
      : AbstractBinarySearchTree<T, DoublyLinkedBinaryTreeNodeInterface<T>>(
            nullptr) {}

  /// Cópia profunda
  DoublyLinkedBinarySearchTree(const DoublyLinkedBinarySearchTree &other);

  /// Movimentação: a origem fica vazia
  DoublyLinkedBinarySearchTree(DoublyLinkedBinarySearchTree &&other) noexcept;

  /// Atribuição por cópia ou movimentação (copy-and-swap)
  DoublyLinkedBinarySearchTree &
  operator=(DoublyLinkedBinarySearchTree other) noexcept;

  /// Libera todos os nós
  ~DoublyLinkedBinarySearchTree() override;

  /// Troca o conteúdo com outra árvore, em O(1)
  void swap(DoublyLinkedBinarySearchTree &other) noexcept;

  /// Insere o valor na árvore
  void insert(const T &value) override;

  /// Remove uma ocorrência do valor, se existir (não faz nada caso contrário)
  void remove(const T &value) override;

  /// Busca o valor
  /// @return o nó que o contém ou nullptr; o nó pertence à árvore e deixa de
  /// ser válido se for removido
  [[nodiscard]] const DoublyLinkedBinaryTreeNodeInterface<T> *
  search(const T &value) const override;
};

#include "data-structure/tree/binary_search_tree/DoublyLinkedBinarySearchTree.cpp"

#endif // DATA_STRUCTURE_DOUBLYLINKEDBINARYSEARCHTREE_H
