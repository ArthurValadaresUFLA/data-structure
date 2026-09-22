//
// Created by arthur on 29/07/24.
//

#ifndef DATA_STRUCTURE_OPENADDRESSHASHTABLE_H
#define DATA_STRUCTURE_OPENADDRESSHASHTABLE_H

#include "data-structure/hash/AbstractHashTable.h"
#include "data-structure/hash/interface/HashTableInterface.h"

/**
 * @class OpenAddressHashTable
 * @brief Uma implementação de tabela hash usando endereçamento aberto.
 *
 * Esta classe implementa a estrutura de dados OpenAddressHashTable, que é um
 * tipo de tabela hash que usa endereçamento aberto para resolver colisões. Ele
 * armazena elementos do tipo T e suporta operações básicas como adicionar
 * elementos e verificar se um elemento está presente na tabela.
 *
 * @tparam T O tipo de elementos armazenados na tabela hash.
 *
 * @extends AbstractHashTable<T>
 * @implements HashTableInterface<T>
 *
 * @see AbstractHashTable
 * @see HashTableInterface
 */
template <class T>
class OpenAddressHashTable : AbstractHashTable<T>,
                             public HashTableInterface<T> {
private:
  T *_table = nullptr;

public:
  OpenAddressHashTable(
      std::size_t capacity,
      std::function<std::size_t(T value, std::size_t capacity)> hashFunction);

  /**
   * @brief Constrói um novo objeto OpenAddressHashTable copiando outro objeto
   * OpenAddressHashTable.
   *
   * Este construtor cria um novo objeto OpenAddressHashTable e o inicializa
   * copiando o conteúdo de outro objeto OpenAddressHashTable. A capacidade e a
   * função hash são passadas do outro objeto para o novo objeto. A memória é
   * alocada para a tabela do novo objeto e os elementos são copiados da tabela
   * do outro objeto para a tabela do novo objeto.
   *
   * @param other O objeto OpenAddressHashTable a ser copiado.
   */
  OpenAddressHashTable(const OpenAddressHashTable &other)
      : AbstractHashTable<T>(other._capacity, other._hashFunction) {
    _table = new T[other._capacity];
    for (std::size_t i = 0; i < other._capacity; ++i) {
      _table[i] = other._table[i];
    }
  }

  /**
   * @brief Adiciona um valor ao OpenAddressHashTable.
   *
   * Esta função adiciona o valor especificado ao OpenAddressHashTable. Ele usa
   * a função hash fornecida para calcular o índice onde o valor deve ser
   * colocado. Se o índice já estiver ocupado, ele sondará linearmente até que
   * um slot vazio seja encontrado.
   *
   * @tparam T O tipo de elementos armazenados na tabela hash.
   * @param value O valor a ser adicionado.
   *
   * @see OpenAddressHashTable
   */
  void add(const T &value) override;

  /**
   * @brief Verifica se OpenAddressHashTable contém um valor específico.
   *
   * Esta função verifica se OpenAddressHashTable contém o valor especificado.
   * Ele usa uma estratégia de sondagem linear para resolver colisões durante a
   * pesquisa. A função retorna verdadeiro se o valor for encontrado e falso
   * caso contrário.
   *
   * @tparam T O tipo de elementos armazenados no OpenAddressHashTable.
   * @param value O valor a ser pesquisado no OpenAddressHashTable.
   * @return true se o valor for encontrado, false caso contrário.
   *
   * @see OpenAddressHashTable
   */
  bool contains(const T &value) const override;

  /**
   * @brief Verifica se o OpenAddressHashTable está cheio.
   *
   * @return True se OpenAddressHashTable estiver cheio, caso contrário, false.
   *
   * @see OpenAddressHashTable
   */
  [[nodiscard]] bool isFull() const;

  /**
   * @brief Sobrecarga do operador de atribuição para OpenAddressHashTable.
   *
   * O operador de atribuição permite atribuir o conteúdo de um objeto
   * OpenAddressHashTable para outro objeto OpenAddressHashTable. Se o objeto
   * atribuído contém dados, esses dados são liberados antes da nova atribuição.
   * A capacidade e a função hash são copiadas do objeto de origem, e os
   * elementos da tabela de origem são transferidos para a nova tabela.
   *
   * @param other O objeto OpenAddressHashTable a ser atribuído.
   * @return Uma referência para o objeto OpenAddressHashTable atribuído.
   */
  OpenAddressHashTable &operator=(const OpenAddressHashTable &other) {
    if (this != &other) {
      // Libera a memória alocada anteriormente
      delete[] _table;

      // Copia a capacidade e a função hash
      this->_capacity = other._capacity;
      this->_hashFunction = other._hashFunction;

      // Aloca nova memória e copia os elementos da tabela de origem
      _table = new T[other._capacity];
      for (std::size_t i = 0; i < other._capacity; ++i) {
        _table[i] = other._table[i];
      }
    }
    return *this;
  }
};

#endif // DATA_STRUCTURE_OPENADDRESSHASHTABLE_H
