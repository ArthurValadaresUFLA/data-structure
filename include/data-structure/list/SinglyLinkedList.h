//
// Created by arthur on 19/06/24.
//

#ifndef DATA_STRUCTURE_SINGLYLINKEDLIST_H
#define DATA_STRUCTURE_SINGLYLINKEDLIST_H

#include <cstddef>
#include <functional>

#include "data-structure/list/AbstractSinglyLinkedList.h"
#include "data-structure/list/interface/ListInterface.h"

/// @brief Lista simplesmente encadeada.
///
/// A lista é a dona dos nós que armazena: todos eles são alocados dinamicamente
/// e liberados pelo destrutor, pelas operações de remoção e pela atribuição.
/// A classe segue a regra dos cinco: cópia profunda (os elementos são copiados
/// para novos nós) e movimentação (a lista de origem fica vazia).
/// @tparam T tipo dos elementos armazenados
template <class T>
class SinglyLinkedList : AbstractSinglyLinkedList<T>, public ListInterface<T> {
public:
  /// Construtor público da classe que cria uma lista vazia
  SinglyLinkedList() : AbstractSinglyLinkedList<T>(nullptr, nullptr) {}

  /// Construtor de cópia: copia, em ordem, todos os elementos de other
  SinglyLinkedList(const SinglyLinkedList &other);

  /// Construtor de movimentação: assume os nós de other, que fica vazia
  SinglyLinkedList(SinglyLinkedList &&other) noexcept;

  /// Atribuição por cópia/movimentação (copy-and-swap)
  SinglyLinkedList &operator=(SinglyLinkedList other) noexcept;

  /// Destrutor: libera todos os nós
  ~SinglyLinkedList() override;

  /// Troca o conteúdo desta lista com o de other, em O(1)
  void swap(SinglyLinkedList &other) noexcept;

  /// Acessa o elemento na posição informada, por referência.
  /// @throw std::out_of_range se index >= size()
  T &operator[](std::size_t index) const override;

  /// Retorna a posição da primeira ocorrência de data, ou size() se data não
  /// estiver na lista. Pior caso O(n).
  [[nodiscard]] std::size_t find(const T &data) const override;

  /// Retorna o número de elementos da lista, em O(1)
  [[nodiscard]] std::size_t size() const override;

  /// Verifica, em O(n), se o valor está contido na lista
  [[nodiscard]] bool contains(const T &data) const override;

  /// Adiciona um dado ao início da lista, em O(1)
  void push(const T &data) override;

  /// Adiciona um dado ao final da lista, em O(1)
  void pushBack(const T &data) override;

  /// Insere um elemento de modo que ele passe a ocupar a posição index. Se
  /// index >= size(), o elemento é inserido ao final da lista.
  void insertAt(std::size_t index, T data) override;

  /// Remove o nó do início da lista, libera-o e retorna o valor
  /// @throw std::runtime_error se a lista estiver vazia
  T removeOnBegin() override;

  /// Remove o nó do fim da lista, libera-o e retorna o valor. Como a lista é
  /// simplesmente encadeada, é necessário percorrê-la: O(n).
  /// @throw std::runtime_error se a lista estiver vazia
  T removeAtEnd() override;

  /// Remove o nó na posição informada, libera-o e retorna o valor
  /// @throw std::out_of_range se position >= size()
  T removeAt(std::size_t position) override;

  /// Verifica se a lista está vazia
  [[nodiscard]] bool isEmpty() const override;

  /// Remove todos os elementos para os quais o predicado retornar true. O
  /// predicado recebe a posição do elemento na lista original (sem considerar
  /// as remoções já feitas) e o seu valor.
  void removeWhere(
      std::function<bool(std::size_t index, T value)> predicate) override;
};

#include "data-structure/list/SinglyLinkedList.cpp"

#endif // DATA_STRUCTURE_SINGLYLINKEDLIST_H
