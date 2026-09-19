//
// Created by arthur on 22/06/24.
//

#ifndef DATA_STRUCTURE_ARRAYSTACK_H
#define DATA_STRUCTURE_ARRAYSTACK_H

#include "data-structure/stack/AbstractArrayStack.h"
#include "data-structure/stack/interface/StackInterface.h"

/**
 * @class ArrayStack
 *
 * @brief Implementação de uma pilha de tamanho fixo usando um array.
 *
 * A classe ArrayStack implementa uma pilha de tamanho fixo usando um array.
 * Ele herda da classe AbstractArrayStack para fornecer a estrutura básica e
 * a funcionalidade para uma pilha, e implementa a interface StackInterface
 * para fornecer as operações específicas da pilha.
 *
 * @tparam T O tipo de elementos armazenados na pilha.
 */
template <class T>
class ArrayStack : AbstractArrayStack<T>, public StackInterface<T> {
 public:
  explicit ArrayStack(std::size_t capacity) : AbstractArrayStack<T>(capacity) {}

  /**
   * @brief Coloca um elemento no topo da pilha.
   *
   * Esta função coloca o elemento fornecido no topo da pilha. Se a pilha não
   * estiver cheia, o elemento será adicionado à pilha. Se a pilha estiver
   * cheia, um std::runtime_error será lançado.
   *
   * @param data O elemento a ser adicionado à pilha.
   */
  void stackUp(T data) override;

  /**
   * @brief Desempilha o elemento superior da pilha.
   *
   * Esta função remove e retorna o elemento superior da pilha.
   *
   * @tparam T O tipo de elementos na pilha.
   *
   * @return O elemento superior da pilha.
   *
   * @throw std::runtime_error Se a pilha estiver vazia.
   */
  T unstack() override;

  /**
   * @brief Retorna o elemento no topo da pilha sem removê-lo.
   *
   * Esta função retorna o elemento no topo da pilha sem removê-lo.
   * Se a pilha não estiver vazia, o elemento superior será retornado por
   * referência. Caso contrário, lança um std::runtime_error indicando que a
   * pilha está vazia.
   *
   * @tparam T O tipo de elementos armazenados na pilha.
   *
   * @return O elemento no topo da pilha.
   *
   * @throws std::runtime_error Se a pilha estiver vazia.
   *
   * @see ArrayStack<T>::peek()
   * @see ArrayStack<T>::unstack()
   * @see ArrayStack<T>::size()
   * @see ArrayStack<T>::empty()
   */
  T peek() const override;

  /**
   * @fn size
   *
   * @brief Retorna o número de elementos atualmente na pilha.
   *
   * Esta função retorna o número de elementos atualmente na pilha.
   *
   * @return O número de elementos na pilha.
   */
  [[nodiscard]] size_t size() const override;

  /**
   * @fn bool ArrayStack<T>::empty() const
   *
   * @brief Verifica se a pilha está vazia.
   *
   * Esta função verifica se a pilha está vazia comparando o ponteiro _top
   * para nullptr.
   *
   * @return True se a pilha estiver vazia, false caso contrário.
   */
  [[nodiscard]] bool empty() const override;
};

#endif  // DATA_STRUCTURE_ARRAYSTACK_H
