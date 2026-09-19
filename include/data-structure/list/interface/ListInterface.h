//
// Created by arthur on 19/06/24.
//

#ifndef DATA_STRUCTURE_LINKEDLISTINTERFACE_H
#define DATA_STRUCTURE_LINKEDLISTINTERFACE_H

#include <cstddef>
#include <functional>

/// @brief Interface para uma estrutura de dados de lista vinculada.
///
/// Esta interface fornece as operações básicas que
/// qualquer implementação de uma lista vinculada deve suportar,
/// como push (adicionar à frente), insertAt (inserir em uma posição
/// específica), removeOnBegin (remover da frente), removeAtEnd (remover do
/// final) e muito mais.
/// @tparam T O tipo de dados armazenados na lista vinculada.
template <class T>
class ListInterface {
 public:
  /// Método que adiciona um elemento no início da lista, puramente abstrato
  /// @param data valor a ser armazenado
  virtual void push(const T& data) = 0;

  /// Método para adicionar um elemento no final da lista, puramente abstrato
  /// @param data valor a ser armazenado
  virtual void pushBack(const T& data) = 0;

  /// Método para adicionar um elemento em uma determinada posição.
  /// @param index posição na qual o valor deve ser adicionado
  /// @param data o valor a ser adicionado
  virtual void insertAt(const std::size_t& index, T data) = 0;

  /// Remove um elemento no início da lista, puramente abstrato
  /// @return o valor que fora removido
  virtual T removeOnBegin() = 0;

  /// Remove um elemento no fim da lista, puramente abstrato
  /// @return o valor que fora removido
  virtual T removeAtEnd() = 0;

  /// Remove um elemento na posição informada, puramente abstrato
  /// @return o valor que fora removido
  virtual T removeAt(const std::size_t& position) = 0;

  /// Verifica se a lista está vazia, puramente abstrato
  /// @return um boleano indicando se alista está vazia
  [[nodiscard]] virtual bool isEmpty() const = 0;

  /// Busca um elemento na lista retornando a posição dele, puramente abstrato
  /// @param data valor a ser procurado
  /// @return posição na qual o valor está armazenado
  [[nodiscard]] virtual std::size_t find(const T& data) const = 0;

  /// Método usado para obter o tamanho da lista, puramente abstrato
  /// @return um std::size_t indicando o tamanho
  [[nodiscard]] virtual std::size_t size() const = 0;

  /// Método usado para verificar se um valor está contido na lista, puramente
  /// abstrato
  /// @param data valor a ser buscado
  /// @return boleano indicando se está ou não contido
  [[nodiscard]] virtual bool contains(const T& data) const = 0;

  /// Operador sobrecarregado usado para acessar o elemetno em uma dada posição,
  /// puramente abstrato
  /// @param index posição a ser lida
  /// @return o valor armazenado na posição
  virtual T& operator[](std::size_t index) const = 0;

  /// Método usado para remover um determinado valor da lista mediante a um
  /// predicado que recebe como argumento a posição e o valor, puramente
  /// abstrato
  /// @param predicate função anônima que determina, por meio de um boleano, se
  /// o valor deve ser removido
  virtual void removeWhere(
      std::function<bool(std::size_t index, T value)> predicate) = 0;
};

#endif  // DATA_STRUCTURE_LINKEDLISTINTERFACE_H
