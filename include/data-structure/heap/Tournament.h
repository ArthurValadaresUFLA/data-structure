//
// Created by arthur on 14/08/24.
//

#ifndef DATA_STRUCTURE_TOURNAMENT_H
#define DATA_STRUCTURE_TOURNAMENT_H

#include <cstddef>
#include <optional>
#include <vector>

#include "data-structure/heap/interface/HeapInterface.h"

/**
 * @brief Árvore de torneio (winner tree) que implementa o HeapInterface.
 *
 * Os elementos ficam nas folhas de uma árvore binária completa armazenada em
 * array (2L - 1 posições, onde L é a menor potência de dois >= capacidade;
 * as folhas ocupam as posições L - 1 .. 2L - 2). Cada nó interno guarda o
 * vencedor da disputa entre seus filhos, e a raiz guarda o campeão: o maior
 * elemento segundo o operador `>` de T.
 *
 * Inserir e remover custam O(log L). Inserir em um torneio cheio lança
 * std::runtime_error; remover/espiar um torneio vazio lança std::out_of_range.
 * O armazenamento é um std::vector, então cópia, movimentação e destruição
 * são seguras por construção.
 *
 * @tparam T O tipo de elementos (copiável e comparável com `>`).
 */
template <class T> class Tournament : public HeapInterface<T> {
private:
  mutable std::vector<std::optional<T>> _nodes;
  std::size_t _leaves;
  std::size_t _capacity;
  std::size_t _size = 0;

  /// Recalcula os vencedores dos ancestrais da folha nodeIndex
  void replay(std::size_t nodeIndex);

  /// Escolhe o vencedor da disputa entre os filhos de parent
  [[nodiscard]] const std::optional<T> &winnerOf(std::size_t parent) const;

public:
  /// Cria um torneio vazio
  /// @param capacity número máximo de participantes (folhas utilizáveis)
  explicit Tournament(const std::size_t &capacity);

  /// Cria um torneio com os n elementos do array
  [[nodiscard]] static Tournament<T> from(const T *array, std::size_t n);

  /// Índice do pai de index (a raiz é pai de si mesma)
  [[nodiscard]] std::size_t parentOf(const std::size_t &index) const override;

  /// Índice do filho direito de index
  [[nodiscard]] std::size_t
  rightChildOf(const std::size_t &index) const override;

  /// Índice do filho esquerdo de index
  [[nodiscard]] std::size_t
  leftChildOf(const std::size_t &index) const override;

  /// Retorna o campeão sem removê-lo
  /// @throw std::out_of_range se o torneio estiver vazio
  [[nodiscard]] T peekRoot() const override;

  /// Remove o campeão e refaz as disputas afetadas
  /// @throw std::out_of_range se o torneio estiver vazio
  T removeRoot() override;

  /// Insere um participante e refaz as disputas afetadas
  /// @throw std::runtime_error se o torneio estiver cheio
  void insert(const T &value) override;

  [[nodiscard]] bool isFull() const override;
  [[nodiscard]] bool isEmpty() const override;
  [[nodiscard]] std::size_t getCapacity() const override;
  [[nodiscard]] std::size_t getSize() const override;

  /// Acessa o nó na posição index da árvore (nós vazios não são acessíveis)
  /// @throw std::out_of_range se index estiver fora da árvore ou o nó estiver
  /// vazio
  [[nodiscard]] T &operator[](std::size_t index) const override;
};

#include "data-structure/heap/Tournament.cpp"

#endif // DATA_STRUCTURE_TOURNAMENT_H
