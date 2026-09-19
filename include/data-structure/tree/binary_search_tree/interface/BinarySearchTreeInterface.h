//
// Created by arthur on 29/07/24.
//

#ifndef DATA_STRUCTURE_BINARYSEARCHTREEINTERFACE_H
#define DATA_STRUCTURE_BINARYSEARCHTREEINTERFACE_H

#include "data-structure/tree/node/interface/SinglyLinkedBinaryTreeNodeInterface.h"

/**
 * @class BinarySearchTreeInterface
 *
 * Uma interface para uma estrutura de dados de árvore de pesquisa binária.
 *
 * Esta interface define as operações básicas que podem ser executadas em uma
 * árvore de pesquisa binária. A árvore armazena elementos do tipo T e permite
 * inserção, remoção e busca de elementos.
 */
template <class T>
class BinarySearchTreeInterface {
 public:
  /**
   * @brief Insere um valor na árvore de pesquisa binária.
   *
   * Este método insere um determinado valor na árvore binária de pesquisa.
   *
   * @param value O valor a ser inserido na árvore.
   */
  virtual void insert(const T& value) = 0;

  /**
   * @fn virtual void BinarySearchTreeInterface::remove(const T& valor) = 0;
   *
   * Esta função é responsável por remover um valor específico da árvore binária
   * de busca.
   *
   * @param value O valor a ser removido da árvore de pesquisa binária.
   *
   * @note Se o valor não for encontrado na árvore de pesquisa binária, nenhuma
   * ação imediata será tomada.
   *
   * @warning Esta função assume que a árvore binária de pesquisa não está
   * vazia.
   *
   * @see BinarySearchTreeInterface::inserir
   * @see BinarySearchTreeInterface::search
   */
  virtual void remove(const T& value) = 0;

  /**
   * @fn virtual SinglyLinkedBinaryTreeNodeInterface<T>*
   * BinarySearchTreeInterface<T>::search(const T& value) const
   * @brief Procura um nó na árvore de pesquisa binária que contém o valor
   * fornecido.
   *
   * Esta função procura um nó na árvore de pesquisa binária que contém o valor
   * fornecido.
   *
   * @param value O valor a ser pesquisado na árvore de pesquisa binária.
   * @return Um ponteiro para o nó que contém o valor ou nullptr se o valor não
   * for encontrado na árvore.
   */
  virtual SinglyLinkedBinaryTreeNodeInterface<T>* search(
      const T& value) const = 0;
};

#endif  // DATA_STRUCTURE_BINARYSEARCHTREEINTERFACE_H
