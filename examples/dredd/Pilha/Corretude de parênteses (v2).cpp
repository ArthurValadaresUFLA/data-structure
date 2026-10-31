/*
# Corretude de parênteses (v2)


Faça um programa que lê uma linha de texto e verifica se todo parênteses tem um
correspondente. Assuma que cada sinal de "fecha parênteses" fecha o último "abre
parênteses".

Caso não existam parênteses correspondentes em todos os casos, o programa deve
escrever a posição do erro. A posição do primeiro caractere é zero. Se todos os
parênteses têm correspondentes, o programa deverá escrever "correto" (letras
minúsculas). A posição do erro no caso de um "fecha parênteses" sem
correspondente é a dele mesmo, pois não é preciso olhar o resto do texto para
saber que há erro. A posição do erro no caso de um "abre parênteses" sem
correspondente é a do último "abre parênteses" visto, pois só é possível saber
que ele não tem correspondente ao final do texto.

Este é um exercício de solução de problema usando pilha. A pilha deve ser parte
importante da solução. Faça um programa utilizando somente a estrutura de dado
pilha, respeitando todas as suas propriedades e não utilizando a STL.

### Entradas

```
1. Uma linha de texto (não mais do que 254 caracteres).
```

### Saídas

```
1. A palavra "correto" se todos tiverem correspondentes ou então a posição do
erro.
```

### Exemplo de Entrada

```
func(x, (y+3)*4)
```

### Exemplo de Saída

```
correto
```

### Exemplo de Entrada

```
(idw ( dpq() sho
```

### Exemplo de Saída

```
5
```

### Exemplo de Entrada

```
(12 + 3) * 4 - 2)
```

### Exemplo de Saída

```
16
```
*/

#include <iostream>
#include <string>

#include "data-structure/stack/LinkedStack.h"
#include "data-structure/stack/interface/StackInterface.h"

typedef int Dado;

int main() {

  LinkedStack<Dado> implementacao;
  StackInterface<Dado> &pilha = implementacao;

  std::string txt;
  std::getline(std::cin, txt);

  bool txtValido{true};
  int i{0};

  while (txtValido && i < int(txt.length())) {

    if (txt[i] == '(')
      pilha.stackUp(i);
    else if (txt[i] == ')') {

      if (pilha.empty())
        txtValido = false;
      else
        pilha.unstack();
    }

    i++;
  }

  if (txtValido) {

    if (pilha.empty())
      std::cout << "correto\n";
    else
      std::cout << pilha.peek() << "\n";

  } else {

    std::cout << (i - 1) << "\n";
  }

  return 0;
}
