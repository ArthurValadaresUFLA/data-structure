//
// Created by arthur on 20/06/24.
//

#ifndef DATA_STRUCTURE_ABSTRACTARRAYQUEUE_H
#define DATA_STRUCTURE_ABSTRACTARRAYQUEUE_H

#include <algorithm>
#include <cstddef>

/**
 * @brief Classe base abstrata para uma fila baseada em array.
 *
 * Esta classe fornece funcionalidade básica para uma fila baseada em array.
 * É uma classe abstrata e não pode ser instanciada sozinha.
 * As subclasses devem implementar funcionalidades adicionais conforme
 * necessário.
 *
 * @tparam T O tipo de elementos armazenados na fila.
 */
template <class T>
class AbstractArrayQueue {
 protected:
  T* array = nullptr;
  std::size_t _capacity;
  T* _begin = nullptr;
  T* _end = nullptr;

  /**
   * @brief Constroi um novo objeto AbstractArrayQueue.
   *
   * Este construtor inicializa o objeto AbstractArrayQueue com a capacidade
   * inicial fornecida. Aloca memória para o array usado para armazenar os
   * elementos da fila.
   *
   * @tparam T O tipo de elementos armazenados na fila.
   * @param inicialCapacity A capacidade inicial da fila.
   */
  explicit AbstractArrayQueue(std::size_t initialCapacity)
      : _capacity(initialCapacity) {
    array = new T[initialCapacity];
  }

  /**
   * @brief Construtor de cópia para AbstractArrayQueue.
   *
   * Este construtor cria uma nova instância de AbstractArrayQueue, copiando os
   * dados de outra instância fornecida.
   *
   * @param other A instância de AbstractArrayQueue a ser copiada.
   */
  AbstractArrayQueue(const AbstractArrayQueue& other)
      : _capacity(other._capacity) {
    array = new T[other._capacity];
    std::copy(other.array, other.array + other._capacity, array);
    _begin = array + (other._begin - other.array);
    _end = array + (other._end - other.array);
  }

  /**
   * @brief Operador de atribuição para AbstractArrayQueue.
   *
   * Este operador permite a atribuição de uma instância de AbstractArrayQueue
   * para outra.
   *
   * @param other A instância de AbstractArrayQueue a ser atribuída.
   * @return Referência para a instância atual após a atribuição.
   */
  AbstractArrayQueue& operator=(const AbstractArrayQueue& other) {
    if (this == &other) {
      return *this;  // Evita auto-atribuição
    }

    delete[] array;  // Libera a memória existente

    _capacity = other._capacity;
    array = new T[other._capacity];
    std::copy(other.array, other.array + other._capacity, array);
    _begin = array + (other._begin - other.array);
    _end = array + (other._end - other.array);

    return *this;
  }
};

#endif  // DATA_STRUCTURE_ABSTRACTARRAYQUEUE_H
