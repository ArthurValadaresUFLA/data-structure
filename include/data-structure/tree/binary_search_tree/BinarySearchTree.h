//
// Created by arthur on 29/07/24.
//

#ifndef DATA_STRUCTURE_BINARYSEARCHTREE_H
#define DATA_STRUCTURE_BINARYSEARCHTREE_H

#include <tuple>

#include "data-structure/tree/binary_search_tree/AbstractBinarySearchTree.h"
#include "data-structure/tree/binary_search_tree/interface/BinarySearchTreeInterface.h"
#include "data-structure/tree/node/SinglyLinkedBinaryTreeNode.h"

/**
 * @class BinarySearchTree
 * @brief Representa uma árvore de pesquisa binária.
 *
 * A classe BinarySearchTree representa uma árvore de pesquisa binária que
 * implementa BinarySearchTreeInterface. Armazena elementos do tipo T e fornece
 * operações para inserir, remover e pesquisar elementos.
 *
 * @tparam T O tipo de valor armazenado na árvore.
 */
template <class T>
class BinarySearchTree : AbstractBinarySearchTree<T>,
                         public BinarySearchTreeInterface<T> {
private:
  /**
   * @brief Retorna uma tupla contendo o nó mínimo e seu pai na árvore.
   *
   * Esta função retorna uma tupla contendo o nó mínimo e seu pai na árvore,
   * começando no nó fornecido. O nó mínimo é determinado iterando repetidamente
   * para o filho esquerdo até que nenhum outro filho esquerdo seja encontrado.
   *
   * @tparam T O tipo de valor armazenado na árvore.
   * @param node O nó inicial para a pesquisa mínima.
   * @return Uma tupla contendo o nó mínimo e seu pai.
   */
  std::tuple<SinglyLinkedBinaryTreeNodeInterface<T> *,
             SinglyLinkedBinaryTreeNodeInterface<T> *>
  treeMinimum(const SinglyLinkedBinaryTreeNode<T> &node);

  /**
   * @brief Procure um nó com o valor fornecido na árvore de pesquisa binária.
   *
   * Esta função procura um nó com o valor fornecido na árvore de pesquisa
   * binária. Retorna uma tupla contendo o pai e o nó atual. Se o valor for
   * encontrado, o pai será o pai do nó com o valor, e o nó atual será o nó com
   * o valor. Se o valor não for encontrado, o nó pai e o nó atual serão
   * nullptr.
   *
   * @tparam T O tipo de valor armazenado na árvore.
   * @param value O valor a ser pesquisado.
   * @return std::tuple<SinglyLinkedBinaryTreeNodeInterface<T> *,
   * SinglyLinkedBinaryTreeNodeInterface<T> *> Uma tupla contendo o pai e o nó
   * atual.
   */
  std::tuple<SinglyLinkedBinaryTreeNodeInterface<T> *,
             SinglyLinkedBinaryTreeNodeInterface<T> *>
  _search(const T &value) const;

  /**
   * @brief Transplanta a subárvore com raiz em 'rootOn' para a posição
   * anteriormente ocupada por 'subárvore'.
   *
   * Esta função é utilizada na operação de remoção de uma árvore binária de
   * busca. Substitui a subárvore "rootOn" por "subárvore", removendo
   * efetivamente "rootOn" de sua posição original e colocando "subárvore" em
   * seu lugar.
   *
   * @param rootOn A raiz da subárvore que está sendo substituída.
   * @param rootOnParent O pai da subárvore 'rootOn'.
   * @param subtree A subárvore que substituirá 'rootOn'.
   */
  void transplant(SinglyLinkedBinaryTreeNodeInterface<T> *rootOn,
                  SinglyLinkedBinaryTreeNodeInterface<T> *rootOnParent,
                  SinglyLinkedBinaryTreeNodeInterface<T> *subtree);

public:
  ~BinarySearchTree();

  /**
   * @brief Insira um valor na árvore de pesquisa binária.
   *
   * Esta função insere um valor na árvore binária de pesquisa. O valor é
   *inserido na posição correta de acordo com o seguintes regras:
   * - Se a árvore estiver vazia, o valor se torna a raiz da árvore.
   * - Se o valor for menor que o valor do nó atual, ele é inserido como filho
   *esquerdo do nó atual.
   * - Se o valor for maior ou igual ao valor do nó atual, ele é inserido como
   *filho direito do nó atual.
   *
   * @tparam T O tipo de valor armazenado na árvore.
   * @param value O valor a ser inserido na árvore.
   */
  void insert(const T &value) override;

  /**
   * @brief Remove o valor especificado da árvore de pesquisa binária.
   *
   * Este método remove o valor especificado da árvore de pesquisa binária, se
   * existir. Se o valor for encontrado, ele será removido junto com seu nó
   * associado. Se o valor não for encontrado, nenhuma alteração é feita na
   * árvore.
   *
   * @tparam T O tipo de valor a ser removido.
   * @param value O valor a ser removido.
   */
  void remove(const T &value) override;

  /**
   * @brief Pesquisa um valor na árvore de pesquisa binária.
   *
   * Esta função procura um determinado valor na árvore de pesquisa binária.
   *
   * @param value O valor a ser pesquisado.
   * @return Um ponteiro constante para o nó que contém o valor, se existir,
   * caso contrário, nullptr.
   */
  const SinglyLinkedBinaryTreeNodeInterface<T> *
  search(const T &value) const override;
};

#endif // DATA_STRUCTURE_BINARYSEARCHTREE_H
