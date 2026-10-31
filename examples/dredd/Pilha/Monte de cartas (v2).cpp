/*
# Monte de cartas (v2)


Giovani decidiu ordenar sua grande coleção de cartas de "Yu-Gi-Oh!". Para isso
pediu sua ajuda e lhe informou que queria um monte ordenado em ordem crescente
pelo poder das cartas, e não teria cartas repetidas. Como tinha muitas, ele
decidiu ordenar dois montes em ordem crescente (podendo conter cartas
repetidas). Sua missão agora é ajudar Giovani a unir os dois montes retirando
suas cartas repetidas. Utilizando-se da estrutura da dado fila, faça um programa
que lê duas filas já em ordem crescente e cria uma terceira fila com os valores
das duas primeiras em ordem crescente sem que haja repetição de elementos.

Não é permitido utilizar a STL ou similares para resolver o problema, bem como
acessar os dados desrespeitando as propriedades da estrutura.

### Entradas

```
1. Quantidade de elementos da fila 1.
2. Elementos da fila 1 em ordem crescente.
3. Quantidade de elementos da fila 2.
4. Elementos da fila 2 em ordem crescente.
```

### Saídas

```
1. Elementos da fila de resultados.
```

### Exemplo de Entrada

```
7
1 3 5 7 10 10 11
6
2 4 6 8 10 12
```

### Exemplo de Saída

```
1 2 3 4 5 6 7 8 10 11 12
```
*/

#include <iostream>

#include "data-structure/queue/LinkedQueue.h"
#include "data-structure/queue/interface/QueueInterface.h"

typedef int Dado;

void leituraFila(int tam, QueueInterface<Dado> &fila) {

  int num;

  for (int i{0}; i < tam; i++) {
    std::cin >> num;
    fila.queue(num);
  }
}

// Intercala (merge) as filas A e B, já ordenadas, em C, descartando os dados
// repetidos.
void ordenaMonte(QueueInterface<Dado> &filaA, QueueInterface<Dado> &filaB,
                 QueueInterface<Dado> &filaC) {

  int ultimoEnfifeirado;
  QueueInterface<Dado> *filaMenor;

  while (!filaA.isEmpty() && !filaB.isEmpty()) {

    filaMenor = (filaA.peek() <= filaB.peek()) ? &filaA : &filaB;

    if (filaC.isEmpty() || filaMenor->peek() != ultimoEnfifeirado) {
      ultimoEnfifeirado = filaMenor->dequeue();
      filaC.queue(ultimoEnfifeirado);
    } else
      filaMenor->dequeue();
  }

  while (!filaA.isEmpty()) {

    if (filaC.isEmpty() || filaA.peek() != ultimoEnfifeirado) {
      ultimoEnfifeirado = filaA.dequeue();
      filaC.queue(ultimoEnfifeirado);
    } else
      filaA.dequeue();
  }

  while (!filaB.isEmpty()) {

    if (filaC.isEmpty() || filaB.peek() != ultimoEnfifeirado) {
      ultimoEnfifeirado = filaB.dequeue();
      filaC.queue(ultimoEnfifeirado);
    } else
      filaB.dequeue();
  }
}

int main() {

  LinkedQueue<Dado> implA, implB, implC;
  QueueInterface<Dado> &filaA = implA, &filaB = implB, &filaC = implC;
  int tam;

  std::cin >> tam;
  leituraFila(tam, filaA);

  std::cin >> tam;
  leituraFila(tam, filaB);

  ordenaMonte(filaA, filaB, filaC);

  while (!filaC.isEmpty())
    std::cout << filaC.dequeue() << " ";

  return 0;
}
