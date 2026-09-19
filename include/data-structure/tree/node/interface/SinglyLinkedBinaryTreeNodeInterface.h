//
// Created by arthur on 29/07/24.
//

#ifndef DATA_STRUCTURE_BINARYTREENODEINTERFACE_H
#define DATA_STRUCTURE_BINARYTREENODEINTERFACE_H

#include "data-structure/tree/node/interface/TreeNodeInterface.h"

/**
 * @class SinglyLinkedBinaryTreeNodeInterface
 *
 * @brief O SinglyLinkedBinaryTreeNodeInterface é uma classe de interface que
 * define as funcionalidades de um nó de árvore binária em uma estrutura de
 * árvore binária vinculada individualmente.
 *
 * A interface fornece métodos para obter e definir os nós filhos esquerdo e
 * direito do nó atual, bem como para obter o número de nós filhos.
 *
 * @tparam T O tipo do valor mantido pelo nó.
 */
template <class T>
class SinglyLinkedBinaryTreeNodeInterface : public TreeNodeInterface<T> {
 public:
  /**
   * @brief Este método recupera o nó filho correto do nó atual.
   *
   * @return Um ponteiro para o nó filho certo.
   */
  virtual SinglyLinkedBinaryTreeNodeInterface<T>* getRight() const = 0;

  /**
   * @brief Define o filho certo do nó atual.
   *
   * Este método define o filho certo do nó atual para o nó fornecido.
   *
   * @param right Um ponteiro para o nó filho certo.
   */
  virtual void setRight(SinglyLinkedBinaryTreeNodeInterface<T>* right) = 0;

  /**
   * @brief Obtém o filho esquerdo do nó atual.
   *
   * @return Um ponteiro para o filho esquerdo do nó atual ou nullptr se não
   * existir.
   */
  virtual SinglyLinkedBinaryTreeNodeInterface<T>* getLeft() const = 0;

  /**
   * @brief Define o filho esquerdo do nó atual da árvore binária.
   *
   * Este método define o filho esquerdo do nó da árvore binária atual para o nó
   * especificado.
   *
   * @param left O nó a ser definido como filho esquerdo do nó atual.
   */
  virtual void setLeft(SinglyLinkedBinaryTreeNodeInterface<T>* left) = 0;

  /**
   * @brief Função virtual que retorna o número de nós filhos do nó atual.
   *
   * Esta função deve ser substituída por classes derivadas para fornecer a
   * implementação.
   *
   * @returns O número de nós filhos.
   */
  [[nodiscard]] virtual int childCount() const = 0;
};

#endif  // DATA_STRUCTURE_BINARYTREENODEINTERFACE_H
