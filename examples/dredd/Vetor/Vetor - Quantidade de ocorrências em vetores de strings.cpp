/*
# Vetor - Quantidade de ocorrências em vetores de strings


Faça um programa que receba três listas de strings. Cada lista representa um
conjunto de elementos. Cada lista será digitada em uma linha específica. Será
garantido que as duas primeiras listas serão diferentes.

Seu programa deverá exibir no dispositivo de saída padrão, para cada palavra da
terceira lista, se a palavra em questão apareceu em nenhuma, uma ou nas duas
listas iniciais.

### Entradas

```
1. Três listas de strings. Cada lista será fornecida em uma linha específica,
com a quantidade de palavras no início.
```

### Saídas

```
1. Sequência de valores que denotam se cada palavra da terceira lista apareceu
em nenhuma, uma ou nas duas listas iniciais.
```

### Exemplo de Entrada

```
4 bola garrafa pedra cachorro
3 cachorro pedra pato
5 bola garrafa pato cachorro pedra
```

### Exemplo de Saída

```
1 1 1 2 2
```

### Exemplo de Entrada

```
4 bola garrafa pedra cachorro
3 cachorro pedra pato
2 cachorro pedra
```

### Exemplo de Saída

```
2 2
```

### Exemplo de Entrada

```
4 bola garrafa pedra cachorro
3 cachorro pedra pato
3 cachorro pedra sapato
```

### Exemplo de Saída

```
2 2 0
```
*/

#include <iostream>

void leituraLista(std::string *lista, int tamLista);

bool procuraLista(const std::string &palavra, std::string *lista, int tamLista);

int main() {

  int tamA, tamB, tamC;
  std::string *listaA, *listaB, *listaC;

  std::cin >> tamA;
  listaA = new std::string[tamA];
  leituraLista(listaA, tamA);

  std::cin >> tamB;
  listaB = new std::string[tamB];
  leituraLista(listaB, tamB);

  std::cin >> tamC;
  listaC = new std::string[tamC];
  leituraLista(listaC, tamC);

  int contadorPalavra;

  for (int i{0}; i < tamC; i++) {

    contadorPalavra = 0;
    contadorPalavra += procuraLista(listaC[i], listaA, tamA);
    contadorPalavra += procuraLista(listaC[i], listaB, tamB);

    std::cout << contadorPalavra << " ";
  }

  delete[] listaA;
  delete[] listaB;
  delete[] listaC;

  return 0;
}

bool procuraLista(const std::string &palavra, std::string *lista,
                  int tamLista) {

  int j{0};

  while (j < tamLista && lista[j] != palavra)
    j++;

  return !(j == tamLista);
}

void leituraLista(std::string *lista, int tamLista) {

  for (int i{0}; i < tamLista; i++)
    std::cin >> lista[i];
}
