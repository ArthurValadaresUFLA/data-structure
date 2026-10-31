/*
# Vetores - União de vetores (alocação dinâmica)


Na matemática a união de dois conjuntos A e B é representada por A ∪ B e é
formada por todos os elementos pertencentes a A ou B. Por exemplo, seja A = {1,
2, 3} e B = {4, 5}, então a união destes dois conjuntos será A ∪ B = {1, 2, 3,
4, 5}, porém caso um elemento esteja em ambos os conjuntos ele não irá aparecer
duas vezes no conjunto união, por exemplo, seja A = {1, 2, 3} e B = {1, 2, 4},
assim a união será A ∪ B = {1, 2, 3, 4}.

Utilizando os conceitos de conjunto faça um programa que leia dois vetores A e B
e determine a união. O tamanho de cada vetor será informado pelo usuário.

**Obs.:** Considere que não existirão vetores vazios.

**Obs.2:** Os vetores devem ser alocados dinamicamente.

### Entradas

```
1. Tamanho do vetor A.
2. Elementos do vetor A.
3. Tamanho do vetor B.
4. Elementos do vetor B.
```

### Saídas

```
1. Vetor C representado a união dos vetores A e B.
```

### Exemplo de Entrada

```
3
1 2 3
2
2 4
```

### Exemplo de Saída

```
1 2 3 4
```
*/

#include <cstring>
#include <iostream>

void leituraArr(int *arr, int tamArr);

void printaUniao(int *arrA, int tamA, int *arrB, int tamB);

int main() {

  int tamA, tamB, *arrA, *arrB;

  std::cin >> tamA;
  arrA = new int[tamA];
  leituraArr(arrA, tamA);

  std::cin >> tamB;
  arrB = new int[tamB];
  leituraArr(arrB, tamB);

  printaUniao(arrA, tamA, arrB, tamB);

  delete[] arrA;
  delete[] arrB;
}

void leituraArr(int *arr, int tamArr) {

  for (int i{0}; i < tamArr; i++)
    std::cin >> arr[i];
}

void printaUniao(int *arrA, int tamA, int *arrB, int tamB) {

  int arrUniao[tamA + tamB];
  std::memcpy(arrUniao, arrA, sizeof(int) * tamA);

  int indexUniao{tamA};
  int j;

  for (int i{0}; i < tamB; i++) {

    j = 0;
    while (j < tamA && arrB[i] != arrA[j]) {
      j++;
    }

    if (j == tamA)
      arrUniao[indexUniao++] = arrB[i];
  }

  int indexMenor, ultimoMenor{-9999};

  for (int i{0}; i < indexUniao; i++) {

    indexMenor = -1;

    for (int j{0}; j < indexUniao; j++) {

      if (arrUniao[j] > ultimoMenor &&
          (indexMenor == -1 || arrUniao[j] < arrUniao[indexMenor]))
        indexMenor = j;
    }

    ultimoMenor = arrUniao[indexMenor];
    std::cout << arrUniao[indexMenor] << " ";
  }
}

// void printaUniao(int *arrA, int tamA, int *arrB, int tamB){

//     int indexA{0}, indexB{0};

//     while(indexA < tamA && indexB < tamB){

//         if(arrA[indexA] == arrB[indexB]){
//             std::cout << arrA[indexA] << " ";
//             indexA++;
//             indexB++;
//         }else if(arrA[indexA] < arrB[indexB])
//             std::cout << arrA[indexA++] << " ";
//         else
//             std::cout << arrB[indexB++] << " ";

//     }

//     while(indexA < tamA){

//         std::cout << arrA[indexA] << " ";
//         indexA++;
//     }

//     while(indexB < tamB){

//         std::cout << arrB[indexB] << " ";
//         indexB++;
//     }

// }
