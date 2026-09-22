//
// Created by arthur on 14/08/24.
//

#ifndef DATA_STRUCTURE_MINHEAP_H
#define DATA_STRUCTURE_MINHEAP_H

#include "data-structure/heap/AbstractHeap.h"
#include "data-structure/heap/interface/HeapInterface.h"

/**
 * @class MinHeap
 * @brief Uma classe que representa uma estrutura de dados MinHeap.
 *
 * Esta classe implementa a interface AbstractHeap e fornece a funcionalidade
 * para armazenar e manipular elementos em um heap mínimo binário. Os elementos
 * são armazenados em uma estrutura de dados baseada em array. A raiz do heap
 * contém o elemento mínimo. Os elementos são adicionados ao heap usando o
 * método insert() e removidos do heap usando o método removeRoot(). O heap
 * mantém a propriedade heap, onde o valor em cada nó é menor ou igual aos
 * valores de seus filhos.
 *
 * @tparam T O tipo de elementos a serem armazenados no heap.
 */
template <class T> class MinHeap : AbstractHeap<T> {
private:
  /**
   * @brief Encontre o índice do menor nó filho.
   *
   * Esta função obtém o índice do nó atual, os índices de seus nós filhos
   * esquerdo e direito, e o tamanho da pilha. Ele retorna o índice do menor nó
   * filho entre os dois filhos.
   *
   * @param currNode O índice do nó atual.
   * @param leftChild O índice do nó filho esquerdo.
   * @param rightChild O índice do nó filho certo.
   * @param heapSize O tamanho do heap.
   * @return O índice do menor nó filho.
   */
  [[nodiscard]] size_t findSmallestChild(size_t currNode, size_t leftChild,
                                         size_t rightChild,
                                         size_t heapSize) const;

public:
  explicit MinHeap(const size_t &capacity) : AbstractHeap<T>(capacity) {}

  /**
   * @brief Um método de fábrica estático para criar um objeto MinHeap a partir
   * de um array.
   *
   * Este método pega um array de elementos do tipo T e cria um objeto MinHeap a
   * partir dele. O tamanho do array N é especificado como parâmetro do modelo.
   * O método assume que a matriz é do tamanho N, caso contrário, poderá ocorrer
   * um comportamento indefinido.
   *
   * @tparam N O tamanho da matriz.
   * @param array A matriz de entrada de elementos do tipo T.
   * @return Um objeto MinHeap criado a partir do array de entrada.
   */
  template <std::size_t N>
  [[nodiscard]] static MinHeap<T> from(const T array[N]);

  /**
   * @brief Remove o elemento raiz do MinHeap.
   *
   * Esta função remove o elemento raiz do MinHeap e retorna seu valor.
   * Se o heap estiver vazio, ele lançará uma exceção std::out_of_range com uma
   * mensagem de erro "Heap está vazio, não é possível remover a raiz.".
   *
   * A implementação segue o processo usual para remover o elemento raiz de um
   * MinHeap:
   * - Armazena o valor do elemento raiz.
   * - Substitua o elemento raiz pelo último elemento do heap.
   * - Diminua o tamanho do heap em 1.
   * - Compare o elemento raiz com seus filhos e troque-o com o filho menor, se
   * necessário.
   * - Repita o passo acima até que o elemento esteja na posição correta.
   *
   * @tparam T O tipo de elementos armazenados no MinHeap.
   * @return O valor do elemento raiz removido.
   * @throws std::out_of_range se o heap estiver vazio.
   */
  T removeRoot() const override;

  /**
   * @brief Insere um novo valor no heap.
   *
   * Esta função insere um novo valor no heap. O valor é colocado na posição
   * apropriada de acordo com a propriedade heap, que afirma que o valor em cada
   * nó deve ser menor ou igual aos valores de seus filhos. O processo de
   * inserção começa na parte inferior do heap e sobe até que o valor esteja na
   * posição correta.
   *
   * @tparam T O tipo de elementos armazenados no heap.
   * @param valor O valor a ser inserido.
   */
  void insert(const T &value) override;
};

#endif // DATA_STRUCTURE_MINHEAP_H
