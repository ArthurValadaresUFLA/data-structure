/*
# Arquivos - Frase codificada


Dado um arquivo texto chamado palavras.txt que possua várias palavras (no máximo
50), uma em cada linha, suponha que exista um arquivo texto numeros.txt com uma
sequência de números inteiros positivos onde cada número representa a posição da
palavra no arquivo palavras.txt (1 representa a primeira palavra, 2 a segunda,
etc.). Faça um programa que leia os dois arquivos e gere um arquivo texto de
saída frase.txt formado pela substituição dos números do arquivo numeros.txt
pelas palavras do arquivo palavras.txt.

### Entradas

```
1. Arquivo texto denominado palavras.txt com uma palavra em cada linha.
2. Arquivo texto denominado numeros.txt com uma sequência de números.
```

### Saídas

```
1. Arquivo texto denominado frase.txt com a substituição dos números do arquivo
numeros.txt pelas palavras do arquivo palavras.txt.
```

### Exemplo de Entrada (palavras.txt)

```
Federal
Lavras
de
Universidade
```

### Exemplo de Entrada (numeros.txt)

```
4 1 3 2
```

### Exemplo de Saída (frase.txt)

```
Universidade Federal de Lavras
```

### Exemplo de Entrada (palavras.txt)

```
maracangalha
vou
eu
pra
```

### Exemplo de Entrada (numeros.txt)

```
3 2 4 1 3 2
```

### Exemplo de Saída (frase.txt)

```
eu vou pra maracangalha eu vou
```
*/

#include <fstream>
#include <iostream>

int main() {

  std::ifstream arqPalavras("palavras.txt"), arqNumeros("numeros.txt");
  std::ofstream arqSaida("frase.txt");
  std::string *palavras = new std::string[50];

  int i{0}, indexPalavra;

  while (arqPalavras >> palavras[i])
    i++;

  while (arqNumeros >> indexPalavra)
    arqSaida << palavras[indexPalavra - 1] << " ";

  delete[] palavras;

  return 0;
}
