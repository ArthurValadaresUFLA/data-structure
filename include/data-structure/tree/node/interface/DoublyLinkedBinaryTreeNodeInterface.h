//
// Created by arthur on 29/07/24.
//

#ifndef DATA_STRUCTURE_DOUBLYLINKEDBINARYTREENODEINTERFACE_H
#define DATA_STRUCTURE_DOUBLYLINKEDBINARYTREENODEINTERFACE_H

#include "data-structure/tree/node/interface/TreeNodeInterface.h"

/**
 * @class DoublyLinkedBinaryTreeNodeInterface
 * @brief Interface para um nó de árvore binária duplamente vinculado.
 *
 * Esta interface define os métodos para um nó de árvore binária duplamente
 * vinculado. É uma classe filha de TreeNodeInterface.
 *
 * @tparam T O tipo do valor armazenado no nó.
 */
template <class T>
class DoublyLinkedBinaryTreeNodeInterface : public TreeNodeInterface<T> {
 public:
  /**
   * @brief Obtenha o nó pai do nó atual.
   *
   * Esta função retorna o nó pai do nó atual.
   *
   * @return Um ponteiro para o nó pai do nó atual.
   */
  virtual DoublyLinkedBinaryTreeNodeInterface<T> *getParent() const = 0;

  /**
   * @brief Define o nó pai do nó atual.
   *
   * Esta função define o nó pai do nó atual. O nó pai é um nó que vem antes do
   * nó atual na árvore binária.
   *
   * @param parent Um ponteiro para o nó pai.
   */
  virtual void setParent(DoublyLinkedBinaryTreeNodeInterface<T> *parent) = 0;

  /**
   * Retorna o filho direito do nó atual.
   *
   * @return Um ponteiro para o filho direito do nó atual.
   * Retorna nullptr se o nó atual não tiver um filho correto.
   */
  virtual DoublyLinkedBinaryTreeNodeInterface<T> *getRight() const = 0;

  /**
   * @brief Define o nó filho correto do nó atual.
   *
   * Esta função define o nó filho direito do nó atual.
   *
   * @param right O ponteiro para o nó filho certo.
   */
  virtual void setRight(DoublyLinkedBinaryTreeNodeInterface<T> *right) = 0;

  /**
   * @brief Recupera o filho esquerdo do nó atual.
   *
   * Este método retorna um ponteiro para o filho esquerdo do nó atual.
   * Se o nó atual não tiver um filho esquerdo, ele retornará nullptr.
   *
   * @return Um ponteiro para o filho esquerdo do nó atual ou nullptr se não
   * houver nenhum filho esquerdo.
   */
  virtual DoublyLinkedBinaryTreeNodeInterface<T> *getLeft() const = 0;

  /**
   * @brief Define o filho esquerdo do nó atual.
   *
   * Este método é usado para definir o filho esquerdo do nó atual em uma árvore
   * binária duplamente vinculada. O nó filho esquerdo é passado como parâmetro.
   *
   * @param left Um ponteiro para o nó filho esquerdo a ser definido.
   */
  virtual void setLeft(DoublyLinkedBinaryTreeNodeInterface<T> *left) = 0;

  /**
   * @brief Obtenha o número de nós filhos.
   *
   * Este método retorna o número de nós filhos que este
   * DoublyLinkedBinaryTreeNodeInterface possui. Os nós filhos são os nós que
   * estão diretamente conectados a este nó por meio de seus ponteiros esquerdo
   * e direito.
   *
   * @return O número de nós filhos.
   */
  [[nodiscard]] virtual int childCount() const = 0;
};

#endif  // DATA_STRUCTURE_DOUBLYLINKEDBINARYTREENODEINTERFACE_H
