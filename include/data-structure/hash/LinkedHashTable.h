//
// Created by arthur on 29/07/24.
//

#ifndef DATA_STRUCTURE_LINKEDHASHTABLE_H
#define DATA_STRUCTURE_LINKEDHASHTABLE_H

#include <cstddef>
#include <functional>
#include <vector>

#include "data-structure/hash/AbstractHashTable.h"
#include "data-structure/hash/interface/HashTableInterface.h"
#include "data-structure/list/DoublyLinkedList.h"

/**
 * @brief Tabela hash com tratamento de colisões por encadeamento externo.
 *
 * Cada posição da tabela guarda uma DoublyLinkedList com os valores cujo hash
 * resulta naquele índice. A tabela se comporta como um conjunto: adicionar um
 * valor já presente não tem efeito. As listas ficam em um std::vector, de modo
 * que cópia, movimentação e destruição são seguras e não vazam memória (regra
 * do zero).
 *
 * @tparam T O tipo de dado armazenado na tabela (comparável com `==`).
 */
template <class T>
class LinkedHashTable : public HashTableInterface<T>,
                        public AbstractHashTable<T> {
private:
  std::vector<DoublyLinkedList<T>> _table;

public:
  /// Cria uma tabela sem capacidade; é preciso atribuir uma tabela válida antes
  /// de usá-la.
  LinkedHashTable() : AbstractHashTable<T>() {}

  /**
   * @brief Cria uma tabela hash com a capacidade e a função hash informadas.
   * @param capacity número de posições (listas) da tabela
   * @param hashFunction função que recebe o valor e a capacidade e retorna um
   * índice; o resultado é reduzido módulo a capacidade
   */
  explicit LinkedHashTable(
      std::size_t capacity,
      std::function<std::size_t(T value, std::size_t capacity)> hashFunction);

  /// Adiciona o valor à tabela, caso ainda não esteja presente
  void add(const T &value) override;

  /// Verifica se o valor está contido na tabela
  [[nodiscard]] bool contains(const T &value) const override;

  /// Remove o valor da tabela, se estiver presente
  void remove(const T &value) override;

  /**
   * @brief Retorna a lista (posição da tabela) à qual o valor pertence.
   * @param value valor cujo hash determina a posição
   * @return referência para a lista; é válida enquanto a tabela existir
   * @throw std::logic_error se a tabela tiver capacidade zero
   */
  DoublyLinkedList<T> &withHashOf(const T &value);
};

#include "data-structure/hash/LinkedHashTable.cpp"

#endif // DATA_STRUCTURE_LINKEDHASHTABLE_H
