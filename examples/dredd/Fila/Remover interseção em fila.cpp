/*
# Remover interseção em fila


Dadas duas filas F1 e F2, implemente o método que remove os elementos de F2,
presentes em F1. F1 deve estar disponível após a remoção dos elementos de F2
para outras operações. As propriedades de fila devem ser estritamente
respeitadas, ou seja: não é permitido o acesso aleatório aos elementos da fila.A
fila deve ser implementada utilizando encadeamento.

### Entradas

```
1. Número de elementos a serem inseridos em F1.
2. Elementos de F1 em ordem de inserção (inserção no fim da fila).
3. Número de elementos a serem inseridos em F2.
4. Elementos de F2 em ordem de inserção (inserção no fim da fila).
```

### Saídas

```
1. Elementos restantes em F1 após a remoção.
```

### Exemplo de Entrada

```
11
4 6 9 10 1 9 2 13 7 3 5
4
9 2 7 3
```

### Exemplo de Saída

```
4 6 10 1 13 5
```
*/

#include <iostream>

#include "data-structure/queue/LinkedQueue.h"
#include "data-structure/queue/interface/QueueInterface.h"

typedef int Dado;

// Remove de filaA todos os dados que também estão em filaB. A ordem relativa
// dos dados restantes de filaA e o conteúdo de filaB são preservados.
void removeIntersecao(QueueInterface<Dado> &filaA,
                      QueueInterface<Dado> &filaB) {

  std::size_t tamA{filaA.size()}, tamB{filaB.size()};
  std::size_t j;
  Dado auxA, auxB;
  bool naoEncontrou;

  for (std::size_t i{0}; i < tamA; i++) {

    j = 0;
    auxA = filaA.dequeue();
    naoEncontrou = true;

    while (j < tamB && naoEncontrou) {

      auxB = filaB.dequeue();

      if (auxB == auxA)
        naoEncontrou = false;

      filaB.queue(auxB);
      j++;
    }

    if (naoEncontrou)
      filaA.queue(auxA);
  }
}

void leituraFila(int tam, QueueInterface<Dado> &fila) {

  int num;

  for (int i{0}; i < tam; i++) {
    std::cin >> num;
    fila.queue(num);
  }
}

int main() {

  LinkedQueue<Dado> implA, implB;
  QueueInterface<Dado> &filaA = implA, &filaB = implB;

  int n;

  std::cin >> n;
  leituraFila(n, filaA);

  std::cin >> n;
  leituraFila(n, filaB);

  removeIntersecao(filaA, filaB);
  std::size_t novoTam{filaA.size()};

  for (std::size_t i{0}; i < novoTam; i++)
    std::cout << filaA.dequeue() << " ";

  return 0;
}
