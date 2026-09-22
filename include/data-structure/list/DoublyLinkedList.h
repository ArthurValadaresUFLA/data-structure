//
// Created by arthur on 20/06/24.
//

#ifndef DATA_STRUCTURE_DOUBLYLINKEDLIST_H
#define DATA_STRUCTURE_DOUBLYLINKEDLIST_H

#include <cstddef>

#include "data-structure/list/AbstractDoublyLinkedList.h"
#include "data-structure/list/interface/ListInterface.h"

/// @brief Lista duplamente encadeada
///
/// Classe que representa uma lista duplemente encadeada
/// @tparam T
template <class T>
class DoublyLinkedList : AbstractDoublyLinkedList<T>, public ListInterface<T> {
private:
  DoublyLinkedList(DoublyLinkedNodeInterface<T> *begin,
                   DoublyLinkedNodeInterface<T> *end)
      : AbstractDoublyLinkedList<T>(begin, end) {}

public:
  /// Construtor público da classe que inicializa todos os atributos
  DoublyLinkedList() : AbstractDoublyLinkedList<T>(nullptr, nullptr) {}

  ~DoublyLinkedList();

  /// Método responsável por sobrecarregar o operador []
  /// de modo a receber um índice e retornar uma referência
  /// constante para o valor contido no respectivo endereço
  /// de memória. Se o índice passado exceder o número de
  /// elementos levanta uma exceção
  T &operator[](std::size_t index) const override;

  /// Método responsável por retornar o tamanho da lista
  /// O tamanho da lista é calculado a cada vez que acessado,
  /// de modo que se itere sobre os nós contituintes
  [[nodiscard]] size_t size() const override;

  /// Método responsável por retornar a posição do dado informado
  /// Este método itera ao longo da lista de modo a não exceder o
  /// número de elementos e, a medida com que o faz, incrementa o
  /// índice do elemento, se o elemento não for achado retorna o
  /// final da lista.
  /// @param data valor a ser buscado
  size_t find(const T &data) const override;

  /// Método responsável por iterar sobre os nós contituintes
  /// e verificar se o valor contido em cada um deles é o valor
  /// procurado. Pior cenário O(n).
  /// @param data valor a ser verificado se está dentro da lista
  bool contains(const T &data) const override;

  /// Método responsável por adiciona um dado ao início da lista encadeada
  /// @param data passado como argumento é encapsulado em um nó duplamente
  /// encadeado, em seguida o elemento subsequente é definido como sendo aquele
  /// que, anteriormente, era o início da lista. O início da lista é atualizado
  /// para apontar para o novo nó. Se conferires a implementação de
  /// [DoublyLinkedNode] verás que o valor padrão para ambos os ponteiros, isto
  /// é, previous e next é, a princípio e se nenhum outro valor for fornecido,
  /// [nullptr]
  /// @param data o valor a ser inserido no início
  void push(const T &data) override;

  /// Método responsável por adicionar um dado ao final de uma lista encadeada
  /// @param data passado como argumento é encapsulado em um nó duplamente
  /// encadeado, em seguida o elemento precedente é definifo como sendo aquee
  /// que, anteriormente, era o fim da lista. O fim da lista é atualizado para
  /// apontar para o novo nó. Se conferires a implementação de
  /// [DoublyLinkedNode] verás que o valor padrão para ambos os ponteiros, isto
  /// é, previous e next é, a princípio e se nenhum outro valor for fornecido,
  /// [nullptr]
  /// @param data o valor a ser inserido no final
  void pushBack(const T &data) override;

  /// Método responsável por inserir um elemento na respectiva posição passada
  /// como argumento. Se a posição passada no argumento não estiver no intervalo
  /// (0,n+1], onde n representa o tamanho da lista, a posição de inserção será
  /// admitida como sendo o limite inferior ou superior, dependendo de qual
  /// limite do intervalo fora excedido, isto é, por exemplo, ao definir index
  /// como sendo n+2, na pŕatica seria equivalente a inserir em n+1. <br> <br>
  /// O método itera sobre os elementos presentes na lista duplamente encadeada
  /// de modo a não exceder o final ou o índice passado como argumento. Um novo
  /// nó duplamente encadeado é alocado dinâmicamente. O nó no respectivo índice
  /// é deslocado para a direita, o nó anterior passa a apontar para o novo nó
  /// como sendo o subsequente e o subsequente, referencia o novo nó como sendo
  /// o anterior a ele.
  /// @param index índice no qual o valor deve ser inserido
  /// @param data o valor a ser inserido
  void insertAt(std::size_t index, T data) override;

  /// Método responsável por remover o nó no início da lista
  /// Uma variável temporária é criada para armazenar o endereço
  /// de memória que antes residia em _begin, _begin passa a apontar
  /// para o nó subsequente e o valor contido no nó removido é retornado
  T removeOnBegin() override;

  /// Método responsável por remover o nó no fim da lista
  /// Uma variável temporária é criada para armazenar o endereço
  /// de memória que antes residia em _end, _end passa a apontar
  /// para o nó subsequente e o valor contido no nó removido é retornado
  T removeAtEnd() override;

  /// Método responsável por remover um nó na posição especificada
  /// Itera ao longo da lista de modo que não exceda o fim ou que
  /// o índice de iteração não exceda a posição informada. Se a
  /// posição for maior que o número de elementos ou menos que 0,
  /// lança uma exceção.
  /// @param position indicando a posição do valor a ser removido
  T removeAt(const std::size_t &position) override;

  /// Método responsável por retornar um booleano indicando se a lista está
  /// vazia ou não.
  [[nodiscard]] bool isEmpty() const override;

  /// Função responsável por remover um elemento mediante um predicado
  /// @param predicate predicado que recebe como argumento o índice e o valor
  /// armazenado dentro da posição.
  void removeWhere(std::function<bool(std::size_t, T)> predicate) override;
};

#endif // DATA_STRUCTURE_DOUBLYLINKEDLIST_H
