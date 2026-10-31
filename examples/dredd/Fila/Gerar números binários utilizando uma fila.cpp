/*
# Gerar números binários utilizando uma fila


Implemente uma estrutura do tipo fila com as operações básicas de inserção e
remoção. Com a estrutura implementada, faça um programa que utilize a fila para
gerar números binários de 1 a N. O trecho a seguir dá uma dica de como resolver
o problema:

```
inicio = "1"
enfileira (inicio) // fila = (1)
laço
        enfileira(inicio + “0”) // fila = (1, 10)
        enfileira(inicio + “1”) // fila(1, 10, 11)
        elemento = desenfileira()
fim  do laço
```

Note que como cada passo do laço enfileira por padrão dois elementos, você
precisará inserir um controle adicional no laço ou na impressão para evitar
enfileirar um elemento a mais, dependendo da entrada.

### Entradas

```
1. Número inteiro positivo representando N
```

### Saídas

```
1. Números binários gerados de 1 a N
```

### Exemplo de Entrada

```
6
```

### Exemplo de Saída

```
1 10 11 100 101 110
```
*/

#include <iostream>
#include <string>

#include "data-structure/queue/LinkedQueue.h"
#include "data-structure/queue/interface/QueueInterface.h"

typedef std::string Dado;

int main() {

  LinkedQueue<Dado> implementacao;
  QueueInterface<Dado> &fila = implementacao;
  int n;
  Dado base{"1"};
  Dado numA, numB;

  std::cin >> n;

  std::cout << base << " ";

  for (int i{0}; i < (n / 2 - 1); i++) {

    numA = base + "0";
    numB = base + "1";

    std::cout << numA << " ";
    std::cout << numB << " ";

    fila.queue(numA);
    fila.queue(numB);

    base = fila.dequeue();
  }

  if (n % 2) { // impar
    std::cout << base + "0" << " ";
    std::cout << base + "1" << "\n";
  } else // par
    std::cout << base + "0" << "\n";

  return 0;
}
