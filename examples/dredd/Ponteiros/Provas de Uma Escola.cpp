/*
# Ponteiros - Provas de Uma Escola


Um escola deseja automatizar o processo de cálculo de notas da seguinte maneira. Um registro para representar um aluno deve ser criado com o número de matrícula e notas de 2 provas.

Uma matriz nxn será alocada dinamicamente e cada posição contará com um ponteiro para o tipo aluno. Os dados de todos os alunos (nxn) devem ser cadastrados, e para cada aluno será criada uma estrutura com alocação dinâmica e o respectivo ponteiro da matriz será atualizado para apontar para essa estrutura.

Após isso, a matriz terá cada coluna ordenada pela nota final do aluno (crescente), que é calculada pela média simples das duas notas.

### Entradas

```
1. Tamanho dos lados da matriz n
2. Sequencia de dados dos nxn alunos
```

### Saídas

```
1. No de Matrícula de cada aluno, na ordem que aparece na matriz.
```

### Exemplo de Entrada

```
2
1 100 90  2 70 80
3 60 60   4 100 100
```

### Exemplo de Saída

```
3 2
1 4
```
*/

#include <iostream>

struct Aluno{
    int matricula, notaA, notaB;
    float media;
};

// bool operator<(const Aluno &alunoA, const Aluno &alunoB){
//     float mediaA{(alunoA.notaA + alunoA.notaB)/2.0};
//     float mediaB{(alunoB.notaA + alunoB.notaB)/2.0};

//     return mediaA < mediaB;
// }

bool operator<(const Aluno &alunoA, const Aluno &alunoB){
    
    return alunoA.media < alunoB.media;
}

void selectionSort(Aluno ***matrizAlunos, int tamMatriz, int indexColuna){

    int indexMenor;
    Aluno *aux;

    for(int i{0}; i<(tamMatriz - 1); i++){

        indexMenor = i;
        for(int j{indexMenor + 1}; j<tamMatriz; j++){

            if((*matrizAlunos[j][indexColuna]) < (*matrizAlunos[indexMenor][indexColuna])){
                indexMenor = j;
            }

        }

        if(indexMenor != i){
            aux = matrizAlunos[i][indexColuna];
            matrizAlunos[i][indexColuna] = matrizAlunos[indexMenor][indexColuna];
            matrizAlunos[indexMenor][indexColuna] = aux;
        }


    }


}

int main(){

    int n;
    std::cin >> n;

    Aluno ***matrizAlunos = new Aluno**[n];
    for(int i{0}; i<n; i++)
        matrizAlunos[i] = new Aluno*[n];

    for(int i{0}; i<n; i++){
        for(int j{0}; j<n; j++){

            matrizAlunos[i][j] = new Aluno;
            std::cin >> matrizAlunos[i][j]->matricula >> matrizAlunos[i][j]->notaA >> matrizAlunos[i][j]->notaB;
            matrizAlunos[i][j]->media = (matrizAlunos[i][j]->notaA + matrizAlunos[i][j]->notaB)/2.0;
        }
    }

    for(int i{0}; i<n; i++)
        selectionSort(matrizAlunos, n, i);


    for(int i{0}; i<n; i++){
        for(int j{0}; j<n; j++){

            std::cout << matrizAlunos[i][j]->matricula << " ";
        }

        std::cout << "\n";
    }


    for(int i{0}; i<n; i++)
        delete[] matrizAlunos[i];
    delete[] matrizAlunos;

    return 0;
}