//
// Created by arthur on 14/08/24.
//

#ifndef DATA_STRUCTURE_MAXHEAP_H
#define DATA_STRUCTURE_MAXHEAP_H

#include <cstddef>

#include "data-structure/heap/AbstractHeap.h"
#include "data-structure/heap/interface/HeapInterface.h"

/**
 * @brief A classe MaxHeap representa uma estrutura de dados de heap máximo
 * binário e implementa o HeapInterface. A raiz é sempre o maior elemento. A
 * ordem é determinada exclusivamente pelo operador `>` de T.
 *
 * O heap possui capacidade fixa; inserir em um heap cheio lança
 * std::runtime_error e remover/espiar um heap vazio lança std::out_of_range.
 * Cópia é profunda e movimentação transfere a posse do armazenamento.
 *
 * @tparam T O tipo de elementos armazenados (precisa ser construível por
 * padrão, copiável e comparável com `>`).
 */
template <class T> class MaxHeap : public AbstractHeap<T> {
public:
  /// Cria um heap vazio
  /// @param capacity o número máximo de elementos
  explicit MaxHeap(const std::size_t &capacity) : AbstractHeap<T>(capacity) {}

  /**
   * @brief Método de fábrica que cria um MaxHeap a partir de um array.
   *
   * Os elementos são inseridos um a um; o heap resultante tem capacidade igual
   * a n.
   *
   * @param array ponteiro para o primeiro elemento (n elementos válidos)
   * @param n quantidade de elementos do array
   * @return o heap construído
   */
  [[nodiscard]] static MaxHeap<T> from(const T *array, std::size_t n);

  /// Remove e retorna a raiz do heap
  /// @throw std::out_of_range se o heap estiver vazio
  T removeRoot() override;

  /// Insere um valor no heap
  /// @throw std::runtime_error se o heap estiver cheio
  void insert(const T &value) override;
};

#include "data-structure/heap/MaxHeap.cpp"

#endif // DATA_STRUCTURE_MAXHEAP_H
