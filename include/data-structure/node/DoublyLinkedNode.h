//
// Created by arthur on 19/06/24.
//

#ifndef DATA_STRUCTURE_DOUBLYLINKEDNODE_H
#define DATA_STRUCTURE_DOUBLYLINKEDNODE_H

#include <tuple>

#include "data-structure/node/AbstractNode.h"
#include "data-structure/node/interface/DoublyLinkedNodeInterface.h"

/// @brief Um nó duplamente vinculado
///
/// Classe genérica usada para representar um
/// nó duplamente encadeado. Herdar
/// de AbstractNode e DoublyLinkedNodeInterface.
/// Observe que no processo de herança,
/// DoubleLinkedNodeInterface é declarado
/// como público, isso é feito para que cada
/// o conteúdo herdado da interface é
/// acessível externamente, enquanto
/// o conteúdo de AbstractNode não está acessível
/// @tparam T o tipo de dados armazenados no nó
template <class T>
class DoublyLinkedNode : AbstractNode<T>, public DoublyLinkedNodeInterface<T> {
private:
  /// Atributo usado para representar o próximo nó
  ///  do tópico. A princípio o
  ///  _valor é nulo.
  DoublyLinkedNodeInterface<T> *_next = nullptr;
  /// Atributo usado para representar um nó anterior
  ///  do tópico. A princípio o
  ///  _valor é nulo.
  DoublyLinkedNodeInterface<T> *_previous = nullptr;

public:
  /// Construtor público usado para inicializar todos os atributos da classe
  /// @param data o valor a ser armazenado no nó
  /// @param próximo ao próximo nó da cadeia
  /// @param anterior ao nó anterior da cadeia
  DoublyLinkedNode(T data, DoublyLinkedNode<T> *next,
                   DoublyLinkedNode<T> *previous)
      : AbstractNode<T>(data), _next(next), _previous(previous) {}

  /// Construtor público usado para inicializar o _value contido no nó e no
  /// próximo nó na cadeia
  /// @param data o valor a ser armazenado no nó
  /// @param próximo ao próximo nó da cadeia
  DoublyLinkedNode(T data, DoublyLinkedNode<T> *next)
      : AbstractNode<T>(data), _next(next), _previous(nullptr) {}

  /// Construtor público usado para inicializar o atributo contido no nó.
  /// O método deve ser declarado com a palavra-chave explícita porque é
  /// um construtor que pode ser chamado com apenas um argumento
  /// @param data o valor a ser armazenado no nó
  explicit DoublyLinkedNode(T data)
      : AbstractNode<T>(data), _next(nullptr), _previous(nullptr) {}

  /// Método Get usado para acessar o próximo atributo, que indica o próximo nó
  /// da cadeia. O método é constante, implementa o que está declarado na
  /// interface e retorna um ponteiro para DoublyLinkedNode
  /// @return próximo nó da cadeia
  DoublyLinkedNodeInterface<T> *getNext() const override;

  /// Obtém o método usado para acessar o atributo anterior, que indica o nó
  /// anterior da cadeia. O método é constante, implementa o que está declarado
  /// na interface e retorna um ponteiro para DoublyLinkedNode
  /// @return o nó anterior da cadeia
  DoublyLinkedNodeInterface<T> *getPrevious() const override;

  /// método get usado para acessar o _value contido em um nó, obtendo uma cópia
  /// dele
  /// @return o _value armazenado na cadeia
  T getData() const override;

  /// Método usado para obter, por referência, o dado armazenado no nó
  /// @returns referência para o dado
  T &getDataRef() override;

  /// método set usado para definir o _value do atributo anterior, baseado no
  /// ponteiro passado como argumento
  /// @param anterior ao nó anterior da cadeia
  void setPrevious(DoublyLinkedNodeInterface<T> *previous) override;

  /// método set usado para definir o _value do próximo atributo, baseado no
  /// ponteiro passado como argumento
  /// @param próximo ao próximo nó da cadeia
  void setNext(DoublyLinkedNodeInterface<T> *next) override;

  /// Método usado para obter ambos os atributos: anterior e próximo
  /// @returns tupla com ambos: nó anterior e seguinte
  std::tuple<DoublyLinkedNodeInterface<T> *, DoublyLinkedNodeInterface<T> *>
  getBoth() const;
};

#include "data-structure/node/DoublyLinkedNode.cpp"

#endif // DATA_STRUCTURE_DOUBLYLINKEDNODE_H
