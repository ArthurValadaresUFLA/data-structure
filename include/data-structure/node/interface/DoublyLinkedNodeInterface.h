//
// Created by arthur on 19/06/24.
//

#ifndef DATA_STRUCTURE_DOUBLYLINKEDNODEINTERFACE_H
#define DATA_STRUCTURE_DOUBLYLINKEDNODEINTERFACE_H

#include "data-structure/node/interface/SinglyLinkedNodeInterface.h"

/// @brief Interface para um nó duplamente encadeado
///
/// Interface usada para representar os métodos que um nó duplamente encadeado
/// deve ter.
/// @tparam T representa o tipo de dado que vai ser armazenado dentro do nó.
template <class T>
class DoublyLinkedNodeInterface : public NodeInterface<T> {
 public:
  /// Método de acesso para o próximo nó do encadeamento, puramente abstrato
  /// @return next node of chain
  virtual DoublyLinkedNodeInterface<T>* getNext() const = 0;

  /// Método para a definição do próximo nó do encadeamento, puramente abstrato
  /// @param next representa o próximo nó do encadeamento
  virtual void setNext(DoublyLinkedNodeInterface<T>* next) = 0;

  /// Método de acesso para o nó antescessor no encadeamento, puramente abstrato
  /// @return nó anterior no encadeamento
  virtual DoublyLinkedNodeInterface<T>* getPrevious() const = 0;

  /// Método de definição do nó anterior no encadeamento, puramente abstrato
  /// @param previous o nó anterior no encadeamento
  virtual void setPrevious(DoublyLinkedNodeInterface<T>* previous) = 0;
};

#endif  // DATA_STRUCTURE_DOUBLYLINKEDNODEINTERFACE_H
