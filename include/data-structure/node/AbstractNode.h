//
// Created by arthur on 19/06/24.
//

#ifndef DATA_STRUCTURE_ABSTRACTNODE_H
#define DATA_STRUCTURE_ABSTRACTNODE_H

/// @brief Classe abstrata contendo os atributos comuns a um nó
///
/// Classe abstrata usada para representar os
/// atributos comuns a todos os tipos de nós
/// encadeados, por exemplo, nós encadeados e
/// duplamente encadeados
/// @tparam T o tipo de dado armazenado dentro do nó
template <class T>
class AbstractNode {
 protected:
  /// Atributo usado para representar
  /// o dado genérico contido dentro
  /// do nó, A princípio, é protegido,
  /// a fim de que os herdeiros da
  /// classe tenham acesso ao atributo
  T _data;

  /// Construto protegido a fim de que os
  /// herdeiros da classe tenham a capacidade
  /// de inicializar os atributos de forma devida
  /// e impedir a instanciação externa, isto é,
  /// contradizer o fato de ser uma classe abstrata
  /// @param data o valor que será a armazenado dentro do nó
  explicit AbstractNode(T data) : _data(data) {}
};

#endif  // DATA_STRUCTURE_ABSTRACTNODE_H
