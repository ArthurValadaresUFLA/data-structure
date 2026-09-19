//
// Created by arthur on 14/08/24.
//

#ifndef DATA_STRUCTURE_MAXHEAP_H
#define DATA_STRUCTURE_MAXHEAP_H

#include "data-structure/heap/AbstractHeap.h"
#include "data-structure/heap/interface/HeapInterface.h"

/**
 * @brief A classe MaxHeap representa uma estrutura de dados de heap máximo
 * binário e implementa o HeapInterface. É uma classe genérica que pode
 * armazenar elementos de qualquer tipo T.
 */
template <class T>
class MaxHeap : AbstractHeap<T>, public HeapInterface<T> {
 public:
  explicit MaxHeap(const size_t &capacity);

  /**
   * @brief Um método de fábrica estático para criar um objeto MaxHeap a partir
   * de um array.
   *
   * Este método pega um array de elementos do tipo T e cria um objeto MaxHeap a
   * partir dele. O tamanho do array N é especificado como parâmetro do modelo.
   * O método assume que a matriz é do tamanho N, caso contrário, poderá ocorrer
   * um comportamento indefinido.
   *
   * @tparam N O tamanho da matriz.
   * @param array A matriz de entrada de elementos do tipo T.
   * @return Um objeto MaxHeap criado a partir do array de entrada.
   */
  template <std::size_t N>
  [[nodiscard]] static MaxHeap<T> from(const T array[N]);

  /**
   * @brief Remove o elemento raiz do MaxHeap.
   *
   * Esta função remove e retorna o elemento raiz do MaxHeap, que é o elemento
   * com o valor mais alto. Se MaxHeap estiver vazio, uma exceção do tipo
   * std::out_of_range será lançada.
   *
   * @return O elemento raiz removido do MaxHeap.
   * @throws std::out_of_range se MaxHeap estiver vazio.
   */
  T removeRoot() const override;

  /**
   * @brief Insere um valor no MaxHeap.
   *
   * Esta função insere um valor no MaxHeap. Ele mantém a propriedade heap
   * comparando o valor com seu pai e trocando-os, se necessário, até
   * o valor está na posição correta.
   *
   * @param value O valor a ser inserido no MaxHeap.
   *
   * @tparam T O tipo de elementos no MaxHeap.
   *
   * @relacionado MaxHeap
   */
  void insert(const T &value) override;
};

#endif  // DATA_STRUCTURE_MAXHEAP_H
