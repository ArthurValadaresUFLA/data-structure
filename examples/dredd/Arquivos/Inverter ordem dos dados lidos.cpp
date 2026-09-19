/*
# Arquivo - Inverter ordem dos dados lidos


Leia um vetor de números inteiros de um arquivo texto "entrada.txt". O número de elementos no arquivo não será informado, mas sabe-se que o arquivo contém no máximo 100 números. Seu trabalho é escrever um arquivo "saida.txt", com os dados do arquivo lido, mas escritos em ordem inversa. Ou seja, o primeiro valor lido deverá ser o último escrito, e vice-versa.

### Entradas

```
1. Arquivo texto entrada.txt contendo até 100 números inteiros
```

### Saídas

```
1. Arquivo texto saida.txt contendo até 100 números inteiros, com os dados escritos em ordem inversa ao de 
leitura  do arquivo entrada.txt.
```

### Exemplo de Entrada (entrada.txt)

```
8 9 10 11 12 13 20 25 28 30
```

### Exemplo de Saída (saida.txt)

```
30 28 25 20 13 12 11 10 9 8
```

### Exemplo de Entrada (entrada.txt)

```
1 2 3 14 15 16 27 28 29 40 41 42 50 60 70 80 99 101
```

### Exemplo de Saída (saida.txt)

```
101 99 80 70 60 50 42 41 40 29 28 27 16 15 14 3 2 1
```
*/

#include <iostream>
#include <fstream>

void escreveSaidaRecursiva(int *arr, int indexArr, std::ifstream &arqEntrada, std::ofstream &arqSaida){

    if(arqEntrada >> arr[indexArr]){
        escreveSaidaRecursiva(arr, indexArr + 1, arqEntrada, arqSaida);
        arqSaida << arr[indexArr] << " ";
    }

}

int main(){

    std::ifstream arqEntrada("entrada.txt");
    std::ofstream arqSaida("saida.txt");

    int *arr = new int[100];

    escreveSaidaRecursiva(arr, 0, arqEntrada, arqSaida);

    delete[] arr;

    return 0;
}