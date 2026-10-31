//
// Created by arthur on 19/06/24.
//

#ifndef DATA_STRUCTURE_SINGLYLINKEDNODEINTERFACE_H
#define DATA_STRUCTURE_SINGLYLINKEDNODEINTERFACE_H

#include "data-structure/node/interface/NodeInterface.h"

/// @brief Interface para um nó com encadeamento simples
///
/// Interface usada para representar todos os métodos que um nó encadeado deve
/// implementar, isto é, todo nó deve implementar o método get e set para o
/// equivalente ao atributo next
/// @tparam T o tipo de dado armazenado dentro do nó
template <class T> class SinglyLinkedNodeInterface : public NodeInterface<T> {
public:
  /// Método que deve ser implementado a fim de que
  /// o meio externo tenha acesso ao ponteiro que
  /// aponta para o próximo nó do encadeamento, que
  /// deve implementar SinglyLinkedNodeInterface
  /// @return o próximo nó do encadeamento
  virtual SinglyLinkedNodeInterface<T> *getNext() const = 0;

  /// Método que deve ser implementado a fim de que
  /// o meio externo tenha a capacidade de alterar,
  /// definir, o valor do atributo responsável por
  /// apontar o endereço de memória do próximo nó do
  /// encadeamento.
  /// @param next o próximo nó do encadeamento
  virtual void setNext(SinglyLinkedNodeInterface<T> *next) = 0;
};

#endif // DATA_STRUCTURE_SINGLYLINKEDNODEINTERFACE_H
