/*
# Ponteiros - Registros, Ordenação e Ponteiros


Crie um registro para representar alunos, contendo nome, média na disciplina e
número de faltas. Faça um programa que leia as informações de N alunos em um
vetor alocado dinamicamente. Imprima os nomes dos alunos na ordem decrescente
das médias dos alunos.

### Entradas

```
1. Número inteiro N.
2. Sequência de N informações de alunos, na ordem: nome do aluno, média e número
de faltas.
```

### Saídas

```
1. Sequência de N nomes. Os nomes devem ser apresentados em ordem decrescente
das médias dos alunos.
```

### Exemplo de Entrada

```
3
Joao 76.4 10
Maria 87.2 2
Ana 33.7 32
```

### Exemplo de Saída

```
Maria
Joao
Ana
```
*/

#include <cstring>
#include <iostream>

struct Aluno {
  char nome[100];
  float mediaNota;
  int numFaltas;
};

bool operator<(const Aluno &alunoA, const Aluno &alunoB) {
  return alunoA.mediaNota < alunoB.mediaNota;
}

int main() {

  int n, numAlunos{0};
  std::cin >> n;

  Aluno *alunos = new Aluno[n];
  Aluno aluno;

  int j;

  for (int i{0}; i < n; i++) {
    std::cin >> aluno.nome >> aluno.mediaNota >> aluno.numFaltas;

    j = 0;
    while (j < numAlunos && aluno < alunos[j]) {
      j++;
    }

    if (j != numAlunos)
      std::memcpy((alunos + j + 1), alunos + j,
                  sizeof(Aluno) * (numAlunos - j));

    alunos[j] = aluno;
    numAlunos++;
  }

  for (int i{0}; i < numAlunos; i++)
    std::cout << alunos[i].nome << "\n";

  delete[] alunos;

  return 0;
}
