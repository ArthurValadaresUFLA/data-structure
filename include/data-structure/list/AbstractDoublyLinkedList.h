//
// Created by arthur on 20/06/24.
//

#ifndef DATA_STRUCTURE_ABSTRACTDOUBLYLINKEDLIST_H
#define DATA_STRUCTURE_ABSTRACTDOUBLYLINKEDLIST_H

#include "data-structure/node/interface/DoublyLinkedNodeInterface.h"

/// @brief Classe abstrata para uma estrutura de dados de lista duplamente
/// vinculada.
///
/// Esta classe abstrata define as propriedades e métodos básicos exigidos por
/// qualquer implementação de uma lista duplamente vinculada em uma linguagem de
/// programação genérica. Isto usa modelos para permitir qualquer tipo T,
/// tornando-o útil para vários tipos de dados.
/// @tparam T O tipo de elementos armazenados na lista.
template <class T> class AbstractDoublyLinkedList {
protected:
  DoublyLinkedNodeInterface<T> *_begin = nullptr;
  DoublyLinkedNodeInterface<T> *_end = nullptr;

  /// Construtor que inicializa atributos referentes a uma lista duplamente
  /// vinculada
  /// @param begin um objeto que implementa um DoublyLinkedNodeInterface que
  /// representa o início da lista
  /// @param end um objeto que implementa um DoublyLinkedInterface que
  /// representa o fim da lista
  AbstractDoublyLinkedList(DoublyLinkedNodeInterface<T> *begin,
                           DoublyLinkedNodeInterface<T> *end)
      : _begin(begin), _end(end) {}
};

#endif // DATA_STRUCTURE_ABSTRACTDOUBLYLINKEDLIST_H
