/*
# Arquivos - Caracteres não brancos


Faça um programa que abra um arquivo texto chamado "Meu_Arquivo.txt" e conte o
número de caracteres não brancos nele. Escreva o resultado da contagem na saída
padrão.

### Entradas

```
1. O arquivo de texto "Meu_Arquivo.txt".
```

### Saídas

```
1. Número de caracteres não brancos dentro do arquivo.
```

### Exemplo de Arquivo

```
Vou aproveitar os exercicios do dredd para estudar muito e tirar 100 em IALG!!
```

### Exemplo de Saída

```
65
```
*/

#include <fstream>
#include <iostream>

int main() {

  const std::string nomeArq{"Meu_Arquivo.txt"};
  std::ifstream arq(nomeArq);

  char c;
  int contador{0};

  while (arq >> c)
    if (c != 32)
      contador++;

  std::cout << contador << "\n";

  return 0;
}
