//
// Created by arthur on 14/08/24.
//

#ifndef DATA_STRUCTURE_TOURNAMENT_H
#define DATA_STRUCTURE_TOURNAMENT_H

#include <stdexcept>

#include "data-structure/heap/AbstractHeap.h"
#include "data-structure/heap/interface/HeapInterface.h"

/**
 * @class Tournament
 * @brief Uma classe que representa uma pilha de torneio.
 *
 * Esta classe herda da classe AbstractHeap e implementa a funcionalidade
 * específica de um heap de torneio. Um heap de torneio é uma árvore binária
 * completa que satisfaz a propriedade heap, onde cada nó representa um vencedor
 * do torneio entre seus filhos. A raiz da árvore é a vencedora geral, com valor
 * mínimo ou máximo, dependendo do tipo de pilha. Esta classe fornece métodos
 * para inserir valores no heap e remover o elemento raiz.
 *
 * @tparam T O tipo de elementos a serem armazenados no heap.
 */
template <class T> class Tournament : AbstractHeap<T> {
public:
  T removeRoot() const override {
    throw std::runtime_error("Unimplemented error");
  }

  /**
   * @brief Insere um valor no heap
   *
   * Esta função insere um valor no heap. Se o heap estiver cheio, será gerado
   * um runtime_error.
   *
   * @param value O valor a ser inserido no heap
   * @tparam T O tipo de elementos no heap
   */
  void insert(const T &value) override;
};

#endif // DATA_STRUCTURE_TOURNAMENT_H
