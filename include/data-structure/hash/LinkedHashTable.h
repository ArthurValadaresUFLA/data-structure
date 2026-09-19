//
// Created by arthur on 29/07/24.
//

#ifndef DATA_STRUCTURE_LINKEDHASHTABLE_H
#define DATA_STRUCTURE_LINKEDHASHTABLE_H

#include "data-structure/list/DoublyLinkedList.h"
#include "data-structure/hash/AbstractHashTable.h"
#include "data-structure/hash/interface/HashTableInterface.h"

/**
 * @class LinkedHashTable
 * @brief Uma implementação de tabela hash usando uma lista vinculada como
 * estratégia de resolução de colisão.
 *
 * Esta classe representa uma tabela hash que usa uma lista vinculada para lidar
 * com colisões. Ele herda do HashTableInterface e classes AbstractHashTable.
 *
 * @tparam T O tipo de dados armazenados na tabela hash.
 *
 * @see HashTableInterface
 * @see AbstractHashTable
 */
template <class T>
class LinkedHashTable : public HashTableInterface<T>,
                        public AbstractHashTable<T> {
 private:
  DoublyLinkedList<T> *table = nullptr;

 public:
  explicit LinkedHashTable(
      std::size_t capacity,
      std::function<std::size_t (T value, std::size_t capacity)> hashFunction);

  /**
   * @brief Copia o construtor para a classe LinkedHashTable.
   *
   * Este construtor cria um novo objeto LinkedHashTable e copia o conteúdo de
   * outro objeto LinkedHashTable.
   *
   * @tparam T O tipo de dados armazenados na tabela hash.
   * @param other O outro objeto LinkedHashTable do qual copiar.
   *
   * @seeLinkedHashTable
   */
  LinkedHashTable(const LinkedHashTable<T> &other);

  /**
   * @fn void LinkedHashTable<T>::add(const T& valor)
   * @brief Adiciona um elemento à tabela hash.
   *
   * Esta função adiciona o valor especificado à tabela hash. Ele usa a função
   * hash para calcular o índice a ser inserido o valor. Se houver uma colisão,
   * ele usará a estratégia de resolução de colisão da lista vinculada para
   * tratá-la.
   *
   * @tparam T O tipo de dados armazenados na tabela hash.
   *
   * @param value O valor a ser adicionado à tabela hash.
   *
   * @see LinkedHashTable::LinkedHashTable
   */
  void add(const T &value) override;

  /**
   * @brief Verifique se LinkedHashTable contém um determinado valor.
   *
   * Esta função verifica se LinkedHashTable contém um determinado valor
   * calculando seu hash, encontrar o índice na tabela e, em seguida, verificar
   * o valor no DoublyLinkedList correspondente.
   *
   * @tparam T O tipo de dados armazenados no LinkedHashTable.
   * @param value O valor a ser verificado.
   * @return True se o valor for encontrado em LinkedHashTable, false caso
   * contrário.
   */
  bool contains(const T &value) const override;

  /**
   * @brief Remove um valor do LinkedHashTable.
   *
   * Esta função remove um determinado valor do LinkedHashTable. Ele usa a
   * função hash para determinar o índice do valor na tabela e remove-o da
   * DoublyLinkedList correspondente.
   *
   * @tparam T O tipo de dados armazenados na tabela.
   * @param value O valor a ser removido da tabela.
   */
  void remove(const T &value) const;

  /**
   * @brief Adds the value to the DoublyLinkedList with the hash value of the
   * given value.
   *
   * This function calculates the hash value of the given value using the hash
   * function defined in the LinkedHashTable and adds the value to the
   * corresponding DoublyLinkedList in the table.
   *
   * @tparam T The type of data stored in the LinkedHashTable.
   * @param value The value to be added to the DoublyLinkedList.
   * @return A reference to the DoublyLinkedList with the hash value of the
   * given value.
   *
   * @see LinkedHashTable
   */
  DoublyLinkedList<T> &withHashOf(const T &value);

  /**
   * @brief Operador de atribuição para a classe LinkedHashTable.
   *
   * Esta função de operador permite a atribuição de um objeto LinkedHashTable
   * para outro.
   *
   * @tparam T O tipo de dados armazenados na tabela hash.
   * @param other O outro objeto LinkedHashTable do qual copiar.
   * @return Uma referência para *this para permitir operações de atribuição
   * encadeadas.
   */
  LinkedHashTable<T> &operator=(const LinkedHashTable<T> &other);
};

#endif  // DATA_STRUCTURE_LINKEDHASHTABLE_H
