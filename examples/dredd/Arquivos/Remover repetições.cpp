/*
# Arquivos - Remover repetições


Faça um programa que lê vários números inteiros de um arquivo texto e escreve os
mesmos números, na mesma ordem, sem as repetições em outro arquivo.

O programa deverá ler do arquivo "entrada.txt" e escrever o resultado no arquivo
"saida.txt"

### Entradas

```
1. A quantidade de números que existem no restante do arquivo.
2. Vários números inteiros para eliminar os repetidos.
```

### Saídas

```
1. Os números lidos, na mesma ordem em que estava, sem as repetições.
```

### Exemplo de Entrada (entrada.txt)

```
13
16 78 4 12 42 25 63 4 8 15 16 23 42
```

### Exemplo de Saída (saida.txt)

```
16 78 4 12 42 25 63 8 15 23
```
*/

#include <fstream>
#include <iostream>

int main() {

  std::ifstream arqEntrada("entrada.txt");
  std::ofstream arqSaida("saida.txt");

  int quantidadeNum, num, j, indexArr{0};
  arqEntrada >> quantidadeNum;

  int *arr = new int[quantidadeNum];

  for (int i{0}; i < quantidadeNum; i++) {
    arqEntrada >> num;
    j = 0;
    while (j < indexArr && arr[j] != num)
      j++;

    if (j == indexArr)
      arr[indexArr++] = num;
  }

  for (int i{0}; i < indexArr; i++)
    arqSaida << arr[i] << " ";

  delete[] arr;

  return 0;
}
