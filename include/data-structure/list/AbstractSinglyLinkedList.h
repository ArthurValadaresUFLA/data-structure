//
// Created by arthur on 19/06/24.
//

#ifndef DATA_STRUCTURE_ABSTRACTLINKEDLIST_H
#define DATA_STRUCTURE_ABSTRACTLINKEDLIST_H

#include "data-structure/node/interface/SinglyLinkedNodeInterface.h"

/// @brief Classe abstrata para uma estrutura de dados de lista vinculada
/// individualmente.
///
/// Esta classe abstrata define as propriedades e métodos básicos exigidos por
/// qualquer implementação de uma lista vinculada individualmente em uma
/// linguagem de programação genérica. Isto usa modelos para permitir qualquer
/// tipo T, tornando-o útil para vários tipos de dados.
/// @tparam T O tipo de elementos armazenados na lista.
template <class T>
class AbstractSinglyLinkedList {
 protected:
  SinglyLinkedNodeInterface<T>* _begin = nullptr;
  SinglyLinkedNodeInterface<T>* _end = nullptr;

  /// Construtor que inicializa atributos referentes a uma lista unida
  /// individualmente
  /// @param begin objeto inicial que implementa um SinglyLinkedNodeInterface
  /// que representa o início da lista
  /// @param end objeto final que implementa um SinglyLinkedInterface que
  /// representa o fim da lista
  AbstractSinglyLinkedList(SinglyLinkedNodeInterface<T>* begin,
                           SinglyLinkedNodeInterface<T>* end)
      : _begin(begin), _end(end) {}
};

#endif  // DATA_STRUCTURE_ABSTRACTLINKEDLIST_H
