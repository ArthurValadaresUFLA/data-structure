/*
# Ordenar uma pilha


Implemente um estrutura de dados do tipo pilha com as operações de empilhar e
desempilhar. Adicione um método que, utilizando uma pilha auxiliar, faça a
ordenação crescente da pilha original, com o menor elemento no topo da pilha.
Nenhuma outra estrutura pode ser utilizada além da pilha auxiliar.

### Entradas

```
1. Quantidade de elementos a serem armazenados na pilha
2. Elementos da pilha
```

### Saídas

```
1. Elementos da pilha ordenados
```

### Exemplo de Entrada

```
10
3 8 5 10 2 0 4 11 21 7
```

### Exemplo de Saída

```
0 2 3 4 5 7 8 10 11 21
```

### Exemplo de Entrada

```
15
3 8 5 10 -2 0 14 11 21 75 6 34 -1 9 -5
```

### Exemplo de Saída

```
-5 -2 -1 0 3 5 6 8 9 10 11 14 21 34 75
```
*/

#include <iostream>

#include "data-structure/stack/LinkedStack.h"
#include "data-structure/stack/interface/StackInterface.h"

typedef int Dado;

// Ordena a pilha de modo que o menor elemento fique no topo, usando apenas as
// operações da interface e uma pilha auxiliar.
void ordenarPilha(StackInterface<Dado> &pilha) {

  LinkedStack<Dado> auxiliar;
  StackInterface<Dado> &pilhaAux = auxiliar;
  Dado dadoAux;

  while (!pilha.empty()) {

    dadoAux = pilha.unstack();

    while (!pilhaAux.empty() && dadoAux > pilhaAux.peek())
      pilha.stackUp(pilhaAux.unstack());

    pilhaAux.stackUp(dadoAux);
  }

  // devolve os dados já ordenados para a pilha original. Como transferir de
  // uma pilha para outra inverte a ordem, usamos uma segunda pilha auxiliar
  // para inverter duas vezes e manter o menor elemento no topo.
  LinkedStack<Dado> invertida;
  StackInterface<Dado> &pilhaInvertida = invertida;

  while (!pilhaAux.empty())
    pilhaInvertida.stackUp(pilhaAux.unstack());

  while (!pilhaInvertida.empty())
    pilha.stackUp(pilhaInvertida.unstack());
}

int main() {

  LinkedStack<Dado> implementacao;
  StackInterface<Dado> &pilha = implementacao;

  int n, num;
  std::cin >> n;

  for (int i{0}; i < n; i++) {
    std::cin >> num;
    pilha.stackUp(num);
  }

  ordenarPilha(pilha);

  for (int i{0}; i < n; i++)
    std::cout << pilha.unstack() << " ";

  return 0;
}
