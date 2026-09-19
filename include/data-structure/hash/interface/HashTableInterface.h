//
// Created by arthur on 29/07/24.
//

#ifndef DATA_STRUCTURE_HASHINTERFACE_H
#define DATA_STRUCTURE_HASHINTERFACE_H

#include "data-structure/list/interface/ListInterface.h"

/// @brief Interface usada para representar uma tabela hash
///
/// Interface usada para representar todos
/// os métodos que devem ser implementados
/// dentro de uma tabela hash
/// @tparam T representa o tipo de dado armazenado dentro da tebela hash
template <class T>
class HashTableInterface {
 public:
  /// Método usado para adicionar um valor dentro da tabela hash, puramente
  /// abstrato
  /// @param value representa o valor a ser adicionado
  virtual void add(const T& value) = 0;

  /// Método usado para verificar se o valor está contido dentro da tabela hash,
  /// puramente abstrato
  /// @param value representa o valor a ser buscado
  virtual bool contains(const T& value) const = 0;
};

#endif  // DATA_STRUCTURE_HASHINTERFACE_H
