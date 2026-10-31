/*
# Ponteiro e Arquivo Binário - Vetor dinâmico salvo em arquivo


Faça um programa que guarda números num vetor dinâmico. Não se sabe quantos
números deverão ser armazenados até que se saiba quais são os números.

A estratégia de alocação de memória deve ser a seguinte:

* o vetor é criado inicialmente com capacidade 5,
* conforme é feito o armazenamento de números no vetor, novos espaços de memória
vão sendo alocados, sempre com 5 elementos a mais do que antes.

O programa deverá ler números inteiros positivos de um arquivo binário chamado
dados.bin e depois da entrada padrão. O último número em cada entrada de dados
será um número não positivo, indicando o fim dos números. Considera-se que o
zero não é positivo, conforme pode ser visto no exemplo de entrada.

Ao final da entrada de dados, o programa deverá:

1. Escrever todos os números (não negativos) armazenados.
1. Escrever qual a capacidade atual do vetor.
1. Escrever o número de transformações (realocações na memória) necessárias.
1. Atualizar o arquivo, gravando as alterações (os valores devem ser escritos em
formato binário.).

### Exemplo de Entrada (dados.bin)

```
10 18 15 71 42 41 0
```

### Exemplo de Entrada (entrada padrão)

```
20 18 35 14 13 0
```

### Exemplo de Saída (saida.txt)

```
10 18 15 71 42 41 20 18 35 14 13
15
2
```
*/

#include <cstring>
#include <fstream>
#include <iostream>

void redimensionaArr(int &capacidade, int *&arr) {

  int *novoArr = new int[capacidade + 5];
  std::memcpy(novoArr, arr, sizeof(int) * capacidade);

  delete[] arr;
  arr = novoArr;
  capacidade += 5;
}

void insereArr(int &tamanhoArr, int &capacidade, int *&arr, int num) {

  if (tamanhoArr == capacidade)
    redimensionaArr(capacidade, arr);

  arr[tamanhoArr++] = num;
}

int main() {

  std::fstream arq;
  arq.open("dados.bin", std::ios::in);

  int capacidade{5}, tamArr{0};
  int *arr = new int[capacidade];

  int num;
  arq.read((char *)(&num), sizeof(int));
  while (num > 0) {
    insereArr(tamArr, capacidade, arr, num);
    arq.read((char *)(&num), sizeof(int));
  }

  std::cin >> num;
  while (num > 0) {
    insereArr(tamArr, capacidade, arr, num);
    std::cin >> num;
  }

  for (int i{0}; i < tamArr; i++) {
    std::cout << arr[i] << " ";
  }

  std::cout << "\n" << capacidade << "\n";
  std::cout << (capacidade / 5 - 1) << "\n";

  arq.close();
  arq.open("dados.bin", std::ios::out);
  arq.write((const char *)arr, sizeof(int) * tamArr);

  delete[] arr;

  return 0;
}
