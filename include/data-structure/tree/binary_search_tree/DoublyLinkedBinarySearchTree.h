//
// Created by arthur on 06/08/24.
//

#ifndef DATA_STRUCTURE_DOUBLYLINKEDBINARYSEARCHTREE_H
#define DATA_STRUCTURE_DOUBLYLINKEDBINARYSEARCHTREE_H

#include "data-structure/tree/binary_search_tree/AbstractBinarySearchTree.h"
#include "data-structure/tree/binary_search_tree/interface/BinarySearchTreeInterface.h"
#include "data-structure/tree/node/interface/DoublyLinkedBinaryTreeNodeInterface.h"

/**
 * @class DoublyLinkedBinarySearchTree
 * @brief Representa uma árvore de pesquisa binária duplamente vinculada.
 *
 * Esta classe fornece uma implementação de uma árvore de pesquisa binária
 * duplamente vinculada. Herda da classe AbstractBinarySearchTree e implementa
 * BinarySearchTreeInterface. A árvore armazena elementos do tipo T e suporta
 * operações de inserção, remoção e pesquisa.
 *
 * @tparam T O tipo de valor armazenado na árvore.
 */
template <class T>
class DoublyLinkedBinarySearchTree : AbstractBinarySearchTree<T>,
                                     public BinarySearchTreeInterface<T> {
private:
  /**
   * @brief Encontra o nó com o valor mínimo em uma determinada árvore.
   *
   * Esta função retorna um ponteiro para o nó com o valor mínimo na árvore
   * fornecida. O nó mínimo é encontrado começando no nó fornecido e percorrendo
   * descendo a subárvore esquerda até que o filho esquerdo seja nulo.
   *
   * @tparam T O tipo de valor armazenado na árvore.
   * @param node O nó inicial da pesquisa.
   * @return Um ponteiro para o nó com o valor mínimo ou nullptr se a árvore
   * estiver vazia.
   */
  DoublyLinkedBinaryTreeNodeInterface<T> *
  treeMinimum(const DoublyLinkedBinaryTreeNodeInterface<T> &node);

  /**
   * @brief Método privado para procurar um nó com um determinado valor na
   * árvore. Este método usa o algoritmo de pesquisa binária para encontrar o
   * nó.
   *
   * @tparam T O tipo de valor armazenado na árvore.
   * @param value O valor a ser pesquisado.
   * @return Um ponteiro para o nó encontrado ou nullptr se o nó não for
   * encontrado.
   */
  DoublyLinkedBinaryTreeNodeInterface<T> *_search(const T &value) const;

  /**
   * @brief Transplante uma subárvore para a árvore enraizada em um nó
   * específico.
   *
   * Esta função substitui a subárvore com raiz em `rootOn` pela `subárvore`,
   * transplantando efetivamente a `subárvore` para a árvore.
   *
   * @tparam T O tipo de valor armazenado na árvore.
   * @param rootOn O nó raiz da árvore para a qual transplantar a subárvore.
   * @param subtree O nó raiz da subárvore a ser transplantada.
   */
  void transplant(DoublyLinkedBinaryTreeNodeInterface<T> *rootOn,
                  DoublyLinkedBinaryTreeNodeInterface<T> *subtree);

public:
  ~DoublyLinkedBinarySearchTree();

  /**
   * @brief Insere um valor na árvore de pesquisa binária duplamente vinculada.
   *
   * Esta função insere um valor na árvore de pesquisa binária duplamente
   * vinculada. Ele cria um novo nó com o valor fornecido e, em seguida,
   * percorre a árvore para encontrar a posição adequada para inserir o novo nó.
   * A travessia é feita comparando o valor fornecido com os valores dos nós e
   * movendo-se para a esquerda ou para a direita dependendo da comparação, até
   * que um ponteiro nulo seja alcançado. Uma vez encontrada a posição adequada,
   * o novo nó é anexado à árvore definindo seu pai para o nó encontrado e
   * definindo seu ponteiro esquerdo ou direito dependendo da comparação com o
   * valor do nó pai.
   *
   * @tparam T O tipo de valor a ser inserido na árvore.
   * @param value O valor a ser inserido na árvore.
   * @return nulo
   */
  void insert(const T &value) override;

  /**
   * @brief Remove um nó com um determinado valor da árvore de pesquisa binária
   * duplamente vinculada.
   *
   * Esta função remove um nó com o valor especificado da árvore de pesquisa
   * binária duplamente vinculada. Começa procurando o nó com o valor fornecido
   * usando a função `_search`. Se o nó for encontrado, temos três casos:
   * - Se o nó a ser removido não tiver filho esquerdo, substitua-o pelo filho
   * direito.
   * - Se o nó a ser removido não tiver filho direito, substitua-o pelo filho
   * esquerdo.
   * - Se o nó a ser removido tiver um filho esquerdo e um filho direito,
   * encontre seu sucessor (o nó com o valor mínimo na subárvore direita).
   * Substitua o nó a ser removido pelo seu sucessor e atualize os ponteiros
   * necessários.
   *
   * @tparam T O tipo de valor a ser removido da árvore.
   * @param value O valor a ser removido da árvore.
   * @return nulo
   */
  void remove(const T &value) override;

  /**
   * @brief Procura um nó com um determinado valor na árvore binária de busca.
   *
   * Esta função procura um nó com o valor especificado na árvore de pesquisa
   * binária. Retorna um ponteiro constante para o nó encontrado ou nullptr se o
   * valor não for encontrado.
   *
   * @tparam T O tipo de valor armazenado na árvore.
   * @param value O valor a ser pesquisado.
   * @return Um ponteiro constante para o nó encontrado ou nullptr se o valor
   * não for encontrado.
   */
  const DoublyLinkedBinaryTreeNodeInterface<T> *
  search(const T &value) const override;
};

#endif // DATA_STRUCTURE_DOUBLYLINKEDBINARYSEARCHTREE_H
