//
// Created by arthur on 29/07/24.
//

#ifndef DATA_STRUCTURE_OPENADDRESSHASHTABLE_H
#define DATA_STRUCTURE_OPENADDRESSHASHTABLE_H

#include <cstddef>
#include <functional>
#include <optional>
#include <vector>

#include "data-structure/hash/AbstractHashTable.h"
#include "data-structure/hash/interface/HashTableInterface.h"

/**
 * @brief Tabela hash com endereçamento aberto e sondagem linear.
 *
 * A busca começa na posição dada pela função hash e avança circularmente até
 * achar o valor ou uma posição nunca ocupada. Remover marca a posição como
 * "removida" (lápide), preservando as cadeias de sondagem. A tabela se comporta
 * como um conjunto e possui capacidade fixa. O armazenamento é um std::vector,
 * portanto cópia, movimentação e destruição são seguras (regra do zero).
 *
 * @tparam T O tipo de dado armazenado (comparável com `==`).
 */
template <class T>
class OpenAddressHashTable : public AbstractHashTable<T>,
                             public HashTableInterface<T> {
private:
  struct Slot {
    std::optional<T> value;
    bool removed = false; // lápide: já esteve ocupada
  };

  std::vector<Slot> _table;
  std::size_t _size = 0;

  /// Posição do valor na tabela, ou _capacity se ele não estiver presente
  [[nodiscard]] std::size_t locate(const T &value) const;

public:
  /// Cria uma tabela sem capacidade
  OpenAddressHashTable() : AbstractHashTable<T>() {}

  /**
   * @brief Cria uma tabela com a capacidade e a função hash informadas.
   * @param capacity número de posições da tabela
   * @param hashFunction função que recebe o valor e a capacidade e retorna um
   * índice; o resultado é reduzido módulo a capacidade
   */
  OpenAddressHashTable(
      std::size_t capacity,
      std::function<std::size_t(T value, std::size_t capacity)> hashFunction);

  /// Adiciona o valor, caso ainda não esteja presente
  /// @throw std::runtime_error se o valor for novo e a tabela estiver cheia
  void add(const T &value) override;

  /// Verifica se o valor está contido na tabela
  [[nodiscard]] bool contains(const T &value) const override;

  /// Verifica se todas as posições da tabela estão ocupadas
  [[nodiscard]] bool isFull() const;

  /// Remove o valor da tabela, se estiver presente
  void remove(const T &value) override;
};

#include "data-structure/hash/OpenAddressHashTable.cpp"

#endif // DATA_STRUCTURE_OPENADDRESSHASHTABLE_H
