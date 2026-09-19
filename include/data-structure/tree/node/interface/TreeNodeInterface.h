//
// Created by arthur on 29/07/24.
//

#ifndef DATA_STRUCTURE_TREENODEINTERFACE_H
#define DATA_STRUCTURE_TREENODEINTERFACE_H

/**
 * @class TreeNodeInterface
 * @brief Uma interface para um nó de árvore que armazena um valor do tipo T
 *
 * Esta interface fornece métodos para acessar e modificar o valor de um nó de
 * árvore. Destina-se a ser implementado por classes concretas de nós de árvore.
 *
 * @tparam T O tipo de valor armazenado no nó da árvore
 */
template <class T>
class TreeNodeInterface {
 public:
  /**
   * @brief Obtenha o valor armazenado no nó da árvore.
   *
   * Esta função retorna o valor armazenado no nó da árvore.
   *
   * @tparam T O tipo de valor armazenado no nó.
   * @return O valor armazenado no nó da árvore.
   */
  virtual T getValue() const = 0;

  /**
   * @brief Define o valor do nó da árvore.
   *
   * Esta função virtual permite que classes derivadas definam o valor do nó da
   * árvore.
   *
   * @tparam T O tipo do valor a ser definido.
   * @param value O novo valor a ser definido.
   */
  virtual void setValue(T value) = 0;
};

#endif  // DATA_STRUCTURE_TREENODEINTERFACE_H
