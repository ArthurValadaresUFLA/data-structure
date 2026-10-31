//
// Created by arthur on 22/06/24.
//

#ifndef DATA_STRUCTURE_LINKEDSTACK_H
#define DATA_STRUCTURE_LINKEDSTACK_H

#include <cstddef>

#include "data-structure/stack/AbstractLinkedStack.h"
#include "data-structure/stack/interface/StackInterface.h"

/**
 * @class LinkedStack
 * @brief Representa uma implementação de pilha vinculada.
 *
 * Esta classe é uma classe modelo que representa uma pilha vinculada. Herda de
 * AbstractLinkedStack<T> e implementa a interface StackInterface<T>. Ele
 * fornece funcionalidade básica para manipular uma pilha usando uma estrutura
 * simplesmente ligada. A pilha é dona dos nós: eles são liberados ao
 * desempilhar e no destrutor. Cópia é profunda; movimentação transfere a posse.
 *
 * @tparam T O tipo de dados a serem armazenados na pilha.
 */
template <class T>
class LinkedStack : AbstractLinkedStack<T>, public StackInterface<T> {
public:
  /// Cria uma pilha vazia
  LinkedStack() : AbstractLinkedStack<T>(nullptr) {}

  /// Construtor de cópia profunda (preserva a ordem dos elementos)
  LinkedStack(const LinkedStack &other);

  /// Construtor de movimentação: a pilha de origem fica vazia
  LinkedStack(LinkedStack &&other) noexcept;

  /// Atribuição por cópia ou movimentação (copy-and-swap)
  LinkedStack &operator=(LinkedStack other) noexcept;

  /// Destrutor: libera todos os nós
  ~LinkedStack() override;

  /// Troca o conteúdo com outra pilha, em O(1)
  void swap(LinkedStack &other) noexcept;

  /**
   * @brief Coloca um elemento no topo da pilha.
   *
   * Esta função adiciona o elemento fornecido ao topo da pilha. Ele cria um
   * novo nó que armazena os dados e o torna o novo topo da pilha.
   *
   * @tparam T O tipo de dados a serem armazenados na pilha.
   * @param data Os dados a serem adicionados à pilha.
   */
  void stackUp(T data) override;

  /**
   * @brief Remove e retorna o elemento superior da pilha.
   *
   * Esta função remove e retorna o elemento superior da pilha. Se a pilha
   * estiver vazia, uma exceção runtime_error será lançada.
   *
   * @return O elemento superior da pilha.
   * @throws std::runtime_error se a pilha estiver vazia.
   */
  T unstack() override;

  /**
   * @brief Retorna o valor que está no topo da pilha sem removê-lo.
   *
   * Esta função retorna o valor que está no topo da pilha sem removê-lo. Se a
   * pilha não estiver vazia, retorna o valor. Se a pilha estiver vazia, uma
   * exceção runtime_error será lançada.
   *
   * @tparam T O tipo de dados armazenados na pilha.
   * @return T O valor no topo da pilha.
   * @throws std::runtime_error se a pilha estiver vazia.
   */
  T peek() const override;

  /**
   * @brief Obtenha o tamanho do LinkedStack.
   *
   * Esta função retorna o número de elementos atualmente armazenados no
   * LinkedStack.
   *
   * @return O tamanho do LinkedStack.
   */
  [[nodiscard]] size_t size() const override;

  /**
   * @fn bool LinkedStack::empty() const
   * @brief Verifica se a pilha está vazia.
   *
   * Esta função verifica se a pilha está vazia verificando se a variável membro
   * `_end` é igual a `nullptr`.
   *
   * @return @c true se a pilha estiver vazia, @c false caso contrário.
   */
  [[nodiscard]] bool empty() const override;
};

#include "data-structure/stack/LinkedStack.cpp"

#endif // DATA_STRUCTURE_LINKEDSTACK_H
