//
// Created by arthur on 06/08/24.
//

#ifndef DATA_STRUCTURE_BINARYSEARCHTREE_H
#define DATA_STRUCTURE_BINARYSEARCHTREE_H

#include <tuple>

#include "data-structure/tree/binary_search_tree/AbstractBinarySearchTree.h"
#include "data-structure/tree/binary_search_tree/interface/BinarySearchTreeInterface.h"
#include "data-structure/tree/node/SinglyLinkedBinaryTreeNode.h"

/**
 * @brief Árvore binária de busca com nós simplesmente ligados.
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
class BinarySearchTree : AbstractBinarySearchTree<T>,
                         public BinarySearchTreeInterface<T> {
private:
  using Node = SinglyLinkedBinaryTreeNodeInterface<T>;

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
  BinarySearchTree() : AbstractBinarySearchTree<T>(nullptr) {}

  /// Cópia profunda
  BinarySearchTree(const BinarySearchTree &other);

  /// Movimentação: a origem fica vazia
  BinarySearchTree(BinarySearchTree &&other) noexcept;

  /// Atribuição por cópia ou movimentação (copy-and-swap)
  BinarySearchTree &operator=(BinarySearchTree other) noexcept;

  /// Libera todos os nós
  ~BinarySearchTree() override;

  /// Troca o conteúdo com outra árvore, em O(1)
  void swap(BinarySearchTree &other) noexcept;

  /// Insere o valor na árvore
  void insert(const T &value) override;

  /// Remove uma ocorrência do valor, se existir (não faz nada caso contrário)
  void remove(const T &value) override;

  /// Busca o valor
  /// @return o nó que o contém ou nullptr; o nó pertence à árvore e deixa de
  /// ser válido se for removido
  [[nodiscard]] const SinglyLinkedBinaryTreeNodeInterface<T> *
  search(const T &value) const override;
};

#include "data-structure/tree/binary_search_tree/BinarySearchTree.cpp"

#endif // DATA_STRUCTURE_BINARYSEARCHTREE_H
