//
// Created by arthur on 29/07/24.
//

#ifndef DATA_STRUCTURE_DOUBLYLINKEDBINARYSEARCHTREEINTERFACE_H
#define DATA_STRUCTURE_DOUBLYLINKEDBINARYSEARCHTREEINTERFACE_H

#include "data-structure/tree/node/interface/DoublyLinkedBinaryTreeNodeInterface.h"

/**
 * @class DoublyLinkedBinarySearchTreeInterface
 * Interface @brief para uma árvore de pesquisa binária duplamente vinculada
 *
 * Esta classe define uma interface para uma árvore de pesquisa binária
 * duplamente vinculada. A árvore suporta operações como inserção, remoção e
 * busca de valores na árvore.
 *
 * A árvore é implementada usando uma estrutura Doubly Linked Node, que permite
 * percorrer a árvore nas direções para frente e para trás.
 *
 * @tparam T O tipo de valor armazenado na árvore
 */
template <class T> class DoublyLinkedBinarySearchTreeInterface {
public:
  /// Destrutor virtual, permite destruir a árvore por meio da interface
  virtual ~DoublyLinkedBinarySearchTreeInterface() = default;

  /**
   * @brief Insere um valor na árvore de pesquisa binária.
   *
   * Esta função insere um valor na árvore binária de pesquisa. Isso garante que
   * a árvore permaneça uma árvore de busca binária válida após a operação de
   * inserção.
   *
   * @param value O valor a ser inserido na árvore de pesquisa binária.
   */
  virtual void insert(const T &value) = 0;

  /**
   * @brief Remove um nó com um valor específico da árvore de pesquisa binária.
   *
   * Esta função remove um nó com o valor especificado da árvore de pesquisa
   * binária. Se a árvore não contém o valor, nada é feito.
   *
   * @tparam T O tipo de valor armazenado na árvore.
   * @param value O valor a ser removido da árvore.
   */
  virtual void remove(const T &value) = 0;

  /**
   * @brief Procura um nó com o valor fornecido na árvore de pesquisa binária.
   *
   * Esta função procura um nó com o valor fornecido na árvore de pesquisa
   * binária. Retorna um ponteiro para o nó se encontrado, caso contrário
   * retorna nullptr.
   *
   * @param value O valor a ser pesquisado na árvore de pesquisa binária.
   * @return Um ponteiro para o nó com o valor fornecido ou nullptr se não for
   * encontrado.
   */
  virtual const DoublyLinkedBinaryTreeNodeInterface<T> *
  search(const T &value) const = 0;
};

#endif // DATA_STRUCTURE_DOUBLYLINKEDBINARYSEARCHTREEINTERFACE_H
