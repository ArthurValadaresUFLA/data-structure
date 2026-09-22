//
// Created by arthur on 29/07/24.
//

#ifndef DATA_STRUCTURE_ABSTRACTHASHTABLE_H
#define DATA_STRUCTURE_ABSTRACTHASHTABLE_H

#include <cstddef>
#include <functional>
#include <utility>

/// @brief Classe abstrata de todas as tabelas hash
///
/// AbstractHashTable é usado para representar a
/// ideia abstrata de todas as tabelas hash. Ela
/// armazena todos os atributos comuns as tabelas hash.
/// @tparam T representa o tipo do dado a ser armazenado dentro da tabela hash
template <class T> class AbstractHashTable {
protected:
  /// Atributo responsável por
  /// representar a capacidade
  /// da tabela hash, no que
  /// tange, por exemplo, uma
  /// tabela de endereçamento
  /// aberto, representa o tamanho
  /// do vetor alocado dinamicamente.
  /// É declarado protegido a fim de
  /// que somente os herdeiros da
  /// classe possam acessar e alterar
  /// o seu valor
  std::size_t _capacity = 0;

  /// Função hash da tabela. A função
  /// anônima deve ser passada dentro
  /// do contrutor. Recebe o valor no índice e
  /// a capacidade da tabela hash.
  /// É declarado protegido a fim de
  /// que somente os herdeiros da
  /// classe possam acessar e alterar
  /// o seu valor
  std::function<std::size_t(T value, std::size_t capacity)> _hashFunction;

  /// Construtor protegido a fim de manter
  /// a consistência da classe no que tange
  /// ao seu carater abstrato. Recebe a capacidade
  /// que deve ser alocada para a tabela hash e uma
  /// função anônima que representa a função hash
  AbstractHashTable(
      std::size_t capacity,
      std::function<std::size_t(T value, std::size_t capacity)> hashFunction)
      : _capacity(capacity), _hashFunction(std::move(hashFunction)) {}
};

#endif // DATA_STRUCTURE_ABSTRACTHASHTABLE_H
