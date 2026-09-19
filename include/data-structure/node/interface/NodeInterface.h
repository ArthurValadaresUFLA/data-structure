//
// Created by arthur on 19/06/24.
//

#ifndef DATA_STRUCTURE_NODEINTERFACE_H
#define DATA_STRUCTURE_NODEINTERFACE_H

/// @brief Interface para um nó de encadeamento
///
/// Interface usada para representar os métodos que todo
/// nó encadeado deve implementar
/// @tparam T representa o tipo de dado armazenado dentro do nó
template <class T>
class NodeInterface {
 public:
    /// Todo nó deve implementar o método getData
    /// em vista de permitir acesso externo ao conteúdo,
    /// dado, armazenado dentro do nó encadeado
    /// @return o valor armazenado no nó
    virtual T getData() const = 0;
};

#endif  // DATA_STRUCTURE_NODEINTERFACE_H
