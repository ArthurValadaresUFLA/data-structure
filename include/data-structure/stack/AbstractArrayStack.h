//
// Created by arthur on 22/06/24.
//

#ifndef DATA_STRUCTURE_ABSTRACTARRAYSTACK_H
#define DATA_STRUCTURE_ABSTRACTARRAYSTACK_H

#include <cstddef>
#include <stdexcept>

/**
 * @class AbstractArrayStack
 *
 * @brief Classe base abstrata para uma pilha de tamanho fixo implementada
 * usando um array.
 *
 * Esta classe fornece um modelo para implementar uma pilha de tamanho fixo
 * usando um array. Fornece a estrutura básica e a funcionalidade necessária
 * para uma pilha, mas não fornece a implementação para as operações reais da
 * pilha, como push() e pop(). As subclasses podem herdar desta classe e
 * implementar essas operações de acordo.
 *
 * @tparam T O tipo de elementos armazenados na pilha.
 */
template <class T>
class AbstractArrayStack {
 protected:
  T* _array = nullptr;
  T* _top = nullptr;

  std::size_t _capacity{};

  /**
   * @brief Constrói um objeto AbstractArrayStack com a capacidade fornecida.
   *
   * Este construtor inicializa um objeto AbstractArrayStack com a capacidade
   * especificada. Aloca memória para o array usando a capacidade fornecida.
   *
   * @param capacidade A capacidade da pilha.
   */
  explicit AbstractArrayStack(std::size_t capacity) : _capacity(capacity) {
    this->_array = new T[capacity];
  }

  ~AbstractArrayStack() { delete[] this->_array; }

  /**
   * Contructor de cópia
   *
   * Cria uma nova instância de AbstractArrayStack como uma cópia de uma
   * instância existente de AbstractArrayStack.
   *
   * @param source A instância a ser copiada.
   */
  AbstractArrayStack(const AbstractArrayStack& source) {
    this->_capacity = source._capacity;
    this->_array = new T[source._capacity];
    std::copy(source._array, source._array + source._capacity, this->_array);
    this->_top = this->_array + (source._top - source._array);
  }

  AbstractArrayStack& operator=(const AbstractArrayStack& source) {
    if (this != &source) {
      delete[] this->_array;
      this->_capacity = source._capacity;
      this->_array = new T[source._capacity];
      std::copy(source._array, source._array + source._capacity, this->_array);
      this->_top = this->_array + (source._top - source._array);
    }
    return *this;
  }
};

#endif  // DATA_STRUCTURE_ABSTRACTARRAYSTACK_H
