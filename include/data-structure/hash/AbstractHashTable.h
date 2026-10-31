//
// Created by arthur on 29/07/24.
//

#ifndef DATA_STRUCTURE_ABSTRACTHASHTABLE_H
#define DATA_STRUCTURE_ABSTRACTHASHTABLE_H

#include <cstddef>
#include <functional>
#include <stdexcept>
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
  /// do construtor. Recebe o valor no índice e
  /// a capacidade da tabela hash.
  /// É declarado protegido a fim de
  /// que somente os herdeiros da
  /// classe possam acessar e alterar
  /// o seu valor
  std::function<std::size_t(T value, std::size_t capacity)> _hashFunction;

  AbstractHashTable()
      : _capacity(0), _hashFunction([](T, std::size_t) { return 0; }) {}

  /// Construtor protegido a fim de manter
  /// a consistência da classe no que tange
  /// ao seu caráter abstrato. Recebe a capacidade
  /// que deve ser alocada para a tabela hash e uma
  /// função anônima que representa a função hash
  AbstractHashTable(
      std::size_t capacity,
      std::function<std::size_t(T value, std::size_t capacity)> hashFunction)
      : _capacity(capacity), _hashFunction(std::move(hashFunction)) {
    if (not _hashFunction) {
      throw std::invalid_argument("The hash function must be callable");
    }
  }

  /// Calcula o índice da tabela ao qual o valor pertence. O resultado da
  /// função hash é reduzido módulo a capacidade, garantindo um índice válido.
  /// @param value valor cujo índice deve ser calculado
  /// @throw std::logic_error se a tabela tiver capacidade zero
  [[nodiscard]] std::size_t indexOf(const T &value) const {
    if (_capacity == 0) {
      throw std::logic_error("The hash table has no capacity");
    }
    return _hashFunction(value, _capacity) % _capacity;
  }
};

#endif // DATA_STRUCTURE_ABSTRACTHASHTABLE_H
