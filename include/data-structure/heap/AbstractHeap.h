//
// Created by arthur on 14/08/24.
//

#ifndef DATA_STRUCTURE_ABSTRACTHEAP_H
#define DATA_STRUCTURE_ABSTRACTHEAP_H

#include <algorithm>
#include <cstddef>

#include "data-structure/heap/interface/HeapInterface.h"

/**
 * @class AbstractHeap
 * @brief Uma classe abstrata para implementar estruturas de dados heap.
 *
 * Esta classe fornece uma interface comum e variáveis de membro para estruturas
 * de dados heap. Não deve ser instanciado diretamente, mas subclassificado para
 * implementar um tipo específico de heap.
 *
 * @tparam T O tipo de dados a serem armazenados no heap.
 */
template <class T> class AbstractHeap : public HeapInterface<T> {
protected:
  T *_data;
  T *_top;
  std::size_t _capacity;

  /**
   * @class AbstractHeap
   * @brief Uma classe base para implementar estruturas de dados heap.
   *
   * Esta classe fornece uma interface comum e variáveis de membro para
   * estruturas de dados heap. Não deve ser instanciado diretamente, mas
   * subclassificado para implementar um tipo específico de heap.
   *
   * @tparam T O tipo de dados a serem armazenados no heap.
   */
  explicit AbstractHeap(const std::size_t &capacity)
      : _capacity(capacity), _top(nullptr) {
    _data = new T[capacity];
  }

  /**
   * @brief Destruidor para a classe AbstractHeap.
   *
   * Este destruidor libera a memória alocada para o membro _data da classe
   * AbstractHeap.
   */
  ~AbstractHeap() { delete _data; }

  /**
   * @brief Construtor de cópia para a classe AbstractHeap.
   *
   * Este construtor de cópia cria uma nova instância da classe AbstractHeap,
   * copiando o conteúdo do array _data do objeto original.
   *
   * @param other Referência constante para o objeto a ser copiado.
   */
  AbstractHeap(const AbstractHeap &other);

public:
  /**
   * @brief Retorna o índice do nó pai do índice fornecido.
   *
   * O nó pai de um nó no índice `i` em um heap binário está no índice
   * `(i-1)/2`. Esta função calcula e retorna o índice do nó pai do índice
   * fornecido.
   *
   * @param index O índice do nó cujo índice pai deve ser encontrado.
   * @return O índice do nó pai do índice fornecido.
   */
  size_t parentOf(const size_t &index) override;

  /**
   * Obtenha o índice filho correto de um determinado índice.
   *
   * Esta função calcula e retorna o índice do filho direito do elemento no
   * índice fornecido na estrutura de dados MinHeap. O índice filho certo é
   * calculado multiplicando o índice por 2 e adicionando 1.
   *
   * @param index O índice do elemento cujo índice filho direito deve ser
   * calculado.
   * @return O índice do filho direito do elemento no índice fornecido.
   */
  size_t rightChildOf(const size_t &index) override;

  /**
   * @fn size_t MinHeap::leftChildOf(const size_t &index) const
   * @brief Retorna o índice do filho esquerdo de um nó específico no heap
   * mínimo binário.
   * @param index O índice do nó pai.
   * @return O índice do filho esquerdo do nó pai.
   *
   * Este método calcula e retorna o índice do filho esquerdo de um nó
   * específico no heap mínimo binário. O índice do nó pai é fornecido como
   * parâmetro. O índice do filho esquerdo é calculado multiplicando o índice do
   * nó pai por 2 e adicionando 2 ao resultado.
   * @note Este método é usado para acessar o filho esquerdo de um nó específico
   * no heap mínimo binário.
   */
  size_t leftChildOf(const size_t &index) override;

  /**
   * @brief Retorna o valor da raiz do heap.
   *
   * Esta função retorna o valor da raiz do heap, que é o valor mínimo do heap.
   * A raiz é o primeiro elemento do array.
   *
   * @tparam T O tipo de elementos armazenados no heap.
   * @return O valor da raiz.
   */
  T peekRoot() const override;

  /**
   * @brief Verifica se o MinHeap está cheio.
   *
   * O MinHeap é considerado cheio quando o ponteiro `_top` é igual a
   * o ponteiro `_data` incrementado pela `_capacity`.
   *
   * @return `true` se o MinHeap estiver cheio, `false` caso contrário.
   */
  [[nodiscard]] bool isFull() const override;

  /**
   * @brief Retorna se o heap está vazio.
   *
   * Esta função membro verifica se o heap está vazio. Um heap é considerado
   * vazio se seu ponteiro superior for nullptr.
   *
   * @return true se o heap estiver vazio, false caso contrário.
   */
  [[nodiscard]] bool isEmpty() const override;

  /**
   * @brief Retorna a capacidade do MinHeap.
   *
   * Esta função retorna a capacidade do objeto MinHeap.
   * A capacidade representa o número máximo de elementos que o MinHeap pode
   * conter.
   *
   * @returns A capacidade do MinHeap.
   */
  [[nodiscard]] size_t getCapacity() const override;

  /**
   * @fn size_t MinHeap::getSize() const
   * @brief Obtenha o tamanho do heap.
   *
   * Esta função retorna o número atual de elementos no heap.
   *
   * @return O tamanho da pilha.
   */
  [[nodiscard]] size_t getSize() const override;

  /**
   * @brief Retorna uma referência ao elemento no índice especificado no
   *MinHeap.
   * @param index O índice do elemento a ser acessado.
   * @return Uma referência ao elemento no índice especificado.
   * @throws std::out_of_range Se o índice estiver fora do intervalo.
   *
   * Este operador permite acesso a elementos no MinHeap usando a notação de
   *colchetes. O índice deve ser menor que o tamanho do MinHeap. Se o índice
   *estiver fora do intervalo, uma exceção std::out_of_range será lançada.
   *
   * Exemplo de uso:
   *\código{.cpp}
   * MinHeap<int> pilha;
   * heap.inserir(5);
   * heap.inserir(3);
   * heap.inserir(10);
   * valor interno = pilha[1]; // o valor agora é 3
   * \endcode
   *
   * @see MinHeap::insert()
   * @see MinHeap::getSize()
   */
  T &operator[](std::size_t index) const override;

  /**
   * @brief Sobrecarga do operador de igualdade.
   *
   * Compara dois objetos AbstractHeap para igualdade. Dois heaps são iguais se
   * têm a mesma capacidade e os mesmos elementos no mesmo A.
   *
   * @param other O outro objeto AbstractHeap a ser comparado.
   * @return true se os heaps forem iguais, false caso contrário.
   */
  bool operator==(const AbstractHeap &other) const;

  /**
   * @brief Operador de atribuição para a classe AbstractHeap.
   *
   * Este operador de atribuição permite a cópia de um heap para outro. Se
   * ambos os objetos tiverem a mesma capacidade, os dados serão copiados.
   * Caso contrário, a memória anterior será liberada e uma nova memória
   * será alocada de acordo com a capacidade do outro heap.
   *
   * @param other Referência constante para o objeto a ser copiado.
   * @return Referência para a instância atual após a cópia.
   */
  AbstractHeap &operator=(const AbstractHeap &other) {
    if (this != &other) {
      delete[] _data; // Libera a memória anterior

      _capacity = other._capacity;
      _data = new T[_capacity]; // Aloca nova memória
      std::copy(other._data, other._data + _capacity, _data); // Copia os dados

      _top = &_data[other._top - other._data]; // Ajusta o ponteiro _top
    }
    return *this; // Retorna a instância atual
  }
};

#endif // DATA_STRUCTURE_ABSTRACTHEAP_H
