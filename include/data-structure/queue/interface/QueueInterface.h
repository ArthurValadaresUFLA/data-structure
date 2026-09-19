//
// Created by arthur on 20/06/24.
//

#ifndef DATA_STRUCTURE_QUEUEINTERFACE_H
#define DATA_STRUCTURE_QUEUEINTERFACE_H

#include <cstddef>

/**
 * @class QueueInterface
 * @brief Uma interface para definir operações de fila
 *
 * Esta interface define um conjunto de operações que qualquer implementação de
 * fila deve suportar. A fila segue o princípio First-In-First-Out (FIFO), onde
 * o primeiro elemento que estiver enfileirado será o primeiro a ser retirado da
 * fila.
 *
 * @tparam T O tipo de elementos a serem armazenados na fila
 */
template <class T>
class QueueInterface {
  /**
   * @brief Adiciona um elemento à fila.
   *
   * Esta função virtual é usada para adicionar um elemento à fila.
   * O elemento será colocado no final da fila.
   *
   * @param data O elemento a ser adicionado à fila
   */
  virtual void queue(T data) = 0;

  /**
   * @brief Remove e retorna o primeiro elemento da fila.
   *
   * Esta função virtual é usada para remover e retornar o primeiro elemento da
   * fila. O elemento que foi enfileirado primeiro será aquele retirado da fila.
   *
   * @tparam T O tipo de elementos armazenados na fila
   * @return O elemento que foi retirado da fila
   */
  virtual T dequeue() = 0;

  /**
   * @brief Obtenha o tamanho atual da fila.
   *
   * Esta função virtual é usada para obter o tamanho atual da fila.
   * O tamanho da fila indica o número de elementos atualmente
   * armazenado na fila.
   *
   * @return O tamanho atual da fila
   */
  [[nodiscard]] virtual std::size_t size() const = 0;

  /**
   * @brief Verifica se a fila está vazia.
   *
   * Esta função virtual é usada para verificar se a fila está vazia.
   * Uma fila vazia não possui elementos armazenados nela.
   *
   * @return true se a fila estiver vazia, false caso contrário
   */
  [[nodiscard]] virtual bool isEmpty() const = 0;

  /**
   * @brief Dê uma olhada no primeiro elemento da fila sem removê-lo.
   *
   * Esta função virtual é usada para espiar o primeiro elemento da fila sem
   * removê-lo. O elemento que foi enfileirado primeiro será o retornado.
   *
   * @tparam T O tipo de elementos armazenados na fila
   * @return O primeiro elemento da fila
   */
  virtual T peek() const = 0;
};

#endif  // DATA_STRUCTURE_QUEUEINTERFACE_H
