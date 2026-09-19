//
// Created by arthur on 14/08/24.
//

#include <cstddef>

#ifndef DATA_STRUCTURE_HEAPINTERFACE_H
#define DATA_STRUCTURE_HEAPINTERFACE_H

/**
 * @class HeapInterface
 * Uma interface que define as operações de uma estrutura de dados heap.
 * O heap é uma árvore binária completa que satisfaz a propriedade heap,
 * que é o menor elemento (min-heap) ou o maior elemento (max-heap) na raiz.
 *
 * @tparam T O tipo dos elementos armazenados no heap.
 */
template <class T>
class HeapInterface {
 public:
  /**
   * Recupera o índice do nó pai do índice especificado no heap.
   *
   * @param index Índice do nó.
   * @return O índice do nó pai.
   *
   * @note O índice é passado por referência para evitar cópias desnecessárias.
   * @note A função é declarada como `virtual` para permitir a substituição em
   * classes derivadas.
   * @note O atributo `[[nodiscard]]` indica que o valor de retorno não deve ser
   * ignorado.
   */
  [[nodiscard]] virtual std::size_t parentOf(const std::size_t& index) = 0;

  /**
   * @brief Retorna o índice do filho direito do índice fornecido.
   *
   * Este método é uma função virtual pura definida na classe HeapInterface.
   * Retorna o índice do filho certo do índice fornecido no heap.
   * O filho direito de um nó no índice i pode ser calculado como 2i + 2.
   *
   * @param index O índice do nó pai.
   * @return O índice do filho direito do nó pai.
   */
  [[nodiscard]] virtual std::size_t rightChildOf(const size_t& index) = 0;

  /**
   * @brief Retorna o índice do nó filho esquerdo do índice especificado no
   * heap.
   *
   * Este método é uma função virtual pura definida na classe HeapInterface.
   * Retorna o índice do nó filho esquerdo do índice especificado no heap.
   * O filho esquerdo de um nó no índice i pode ser calculado como 2i + 1.
   *
   * @param index O índice do nó pai.
   * @return O índice do nó filho esquerdo.
   *
   * @note O índice é passado por referência para evitar cópias desnecessárias.
   * @note A função é declarada como `virtual` para permitir a substituição em
   * classes derivadas.
   * @note O atributo `[[nodiscard]]` indica que o valor de retorno não deve ser
   * ignorado.
   */
  [[nodiscard]] virtual std::size_t leftChildOf(const std::size_t& index) = 0;

  /**
   * @brief Retorna o valor do elemento raiz no heap.
   *
   * Esta função virtual deve ser implementada por classes derivadas para
   * retornar o valor do elemento raiz no heap. O elemento raiz é o elemento
   * mínimo (em um heap mínimo) ou o elemento máximo (em um heap máximo).
   *
   * @return O valor do elemento raiz no heap.
   *
   * @note Esta função não modifica o heap.
   * @note Esta função assume que o heap não está vazio.
   * @note O chamador deve garantir que o heap não esteja vazio antes de chamar
   * esta função.
   *
   * @see removeRoot()
   */
  [[nodiscard]] virtual T peekRoot() const = 0;

  /**
   * @brief Função virtual para remover o elemento raiz do heap.
   *
   * Esta função remove o elemento raiz do heap e retorna o
   * valor do elemento removido. A propriedade heap é mantida por
   * ajustando as posições dos elementos restantes na pilha.
   *
   * @return O valor do elemento raiz removido.
   */
  [[nodiscard]] virtual T removeRoot() const = 0;

  /**
   * Esta é uma função virtual que insere um valor no heap.
   *
   * @param value O valor a ser inserido no heap.
   */
  virtual void insert(const T& value) = 0;

  /**
   * @brief Indica se o heap está cheio ou não.
   *
   * Esta função retorna um valor booleano que indica se o heap está cheio ou
   * não. Um heap é considerado cheio quando atinge sua capacidade máxima e não
   * pode armazenar mais elementos.
   *
   * @return true se o heap estiver cheio
   * @return false se o heap não estiver cheio
   */
  [[nodiscard]] virtual bool isFull() const = 0;

  /**
   * @brief Verifica se o heap está vazio.
   *
   * @return true se o heap estiver vazio, false caso contrário.
   *
   * @remark Este método é herdado de HeapInterface<T>.
   */
  [[nodiscard]] virtual bool isEmpty() const = 0;

  /**
   * @fn virtual std::size_t HeapInterface::getCapacity() const = 0
   *
   * Retorna a capacidade máxima do heap.
   *
   * Esta função é uma função virtual pura que deve ser implementada por classes
   * derivadas. Retorna o número máximo de elementos que podem ser armazenados
   * no heap.
   *
   * @return A capacidade máxima do heap.
   */
  [[nodiscard]] virtual std::size_t getCapacity() const = 0;

  /**
   * @brief Esta função de membro virtual é herdada da classe HeapInterface e
   * deve ser implementada por quaisquer classes derivadas. Retorna o tamanho do
   * heap, que representa o número total de elementos atualmente armazenados no
   * heap.
   *
   * @return O tamanho do heap como um valor std::size_t.
   */
  [[nodiscard]] virtual std::size_t getSize() const = 0;

  /**
   * @fn T& HeapInterface::operator[](tamanho_t índice) const
   * @brief Sobrecarga do operador de índice que permite acessar elementos do
   * heap por índice.
   * @param index O índice do elemento a ser acessado.
   * @return Uma referência ao elemento no índice especificado.
   *
   * Este operador permite acessar os elementos do heap pelo seu índice. Retorna
   * uma referência ao elemento no índice especificado.
   *
   * @note O índice deve estar dentro do intervalo válido de índices para o
   * heap.
   * @note Este operador não realiza nenhuma verificação de limites.
   */
  [[nodiscard]] virtual T& operator[](std::size_t index) const = 0;
};

#endif  // DATA_STRUCTURE_HEAPINTERFACE_H
