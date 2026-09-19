//
// Created by arthur on 22/06/24.
//

#ifndef DATA_STRUCTURE_STACKINTERFACE_H
#define DATA_STRUCTURE_STACKINTERFACE_H

#include <cstddef>

/**
 * @class StackInterface
 * @brief Interface para uma estrutura de dados de pilha
 *
 * Esta classe define os métodos que devem ser implementados por uma classe de
 * pilha. A pilha é uma estrutura de dados LIFO (último a entrar, primeiro a
 * sair) onde os elementos são adicionado e removido do topo.
 *
 * @tparam T O tipo dos elementos na pilha
 */
template <class T>
class StackInterface {
 public:
  /**
   * @brief Adiciona um elemento ao topo da pilha.
   *
   * Este método adiciona um elemento ao topo da pilha. O elemento é fornecido
   * como parâmetro.
   *
   * @tparam T O tipo do elemento que está sendo adicionado à pilha.
   * @param data O elemento a ser adicionado à pilha.
   */
  virtual void stackUp(T data) = 0;

  /**
   * @brief Função de interface para remover o elemento superior da pilha
   *
   * Esta função é uma função virtual pura que deve ser implementada em uma
   * classe derivada. Remove e retorna o elemento superior da pilha.
   *
   * @tparam T O tipo de elementos na pilha
   * @return T O elemento superior da pilha
   */
  virtual T unstack() = 0;

  /**
   * @brief Retorna o elemento no topo da pilha sem removê-lo.
   *
   * Este método retorna o elemento no topo da pilha sem removê-lo da pilha.
   *
   * @tparam T O tipo de elementos na pilha.
   *
   * @return O elemento no topo da pilha.
   */
  virtual T peek() const = 0;

  /**
   * @brief Retorna o tamanho da pilha.
   *
   * Esta função deve ser implementada em uma classe que implemente uma
   * estrutura de dados de pilha. O tamanho da pilha representa o número de
   * elementos atualmente armazenados na pilha.
   *
   * @return O tamanho da pilha, como um valor std::size_t.
   */
  [[nodiscard]] virtual std::size_t size() const = 0;

  /**
   * @fn bool StackInterface::empty() const
   * @brief Verifica se a pilha está vazia
   *
   * Esta função verifica se a pilha está vazia retornando um valor booleano.
   *
   * @return True se a pilha estiver vazia, false caso contrário.
   */
  [[nodiscard]] virtual bool empty() const = 0;
};

#endif  // DATA_STRUCTURE_STACKINTERFACE_H
