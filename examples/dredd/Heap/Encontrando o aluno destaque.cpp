/*
# Encontrando o aluno destaque


O professor Bruno, com o intuito de motivar ainda mais os alunos a realizarem as atividades propostas para a sua disciplina, resolveu presentear o aluno que mais teve boas notas em suas atividades. Para isso, você deverá fazer um programa que faça esta classificação, com o intuito de automatizar o processo e aplicar os conceitos das estruturas vistas em Estruturas de Dados.

Os dados são classificados pelas informações básicas do aluno (matricula e nome) e uma lista de atividades realizadas. Para cada atividade, existe sua nota e também a quantidade de tentativas que o aluno realizou.

**Observações:** Para facilitar, a classificação deverá ser feita utilizando a média aritmética simples das notas dos alunos nas atividades (a quantidade de atividades informada será fixa para todos os alunos). O critério de desempate deve ser tomado por: 1) quantidade de tentativas e 2) ordem alfabética.

A resolução deste problema deve ser feita utilizando a estrutura de dados Heap genérica. Ou seja, a implementação dos critérios de desempate não deverá ser realizada dentro de sua estrutura, e sim no TAD especifico para o aluno. Você pode utilizar o [código fornecido](codigoBase.cpp) para agilizar o processo de implementação.

### Entradas

```
1. Quantidade de alunos que serão informados.
2. Número de atividades que será informado de cada aluno.
3. Matricula (número natural) e nome (texto sem espaços) de cada aluno, seguido das atividades do mesmo (nota e tentativas)
```

### Saídas

```
1. Matrícula e nome do aluno destaque no formato: [Matricula] Nome.
```

### Exemplo de Entrada

```
2
3
2015342 Marcos
100 1
30 4
80 2
2014234 Jose
100 1
100 3
100 2
```

### Exemplo de Saída

```
[2014234] Jose
```

### Exemplo de Entrada

```
2
3
2017232 Antonio
100 1
100 4
100 1
2017334 Leonardo
100 3
100 1
100 2
```

### Exemplo de Saída

```
[2017232] Antonio
```

### Exemplo de Entrada

```
3
1
2017211 Bruno
100 1
2017212 Matheus
100 2
2018001 Martha
100 3
```

### Exemplo de Saída

```
[2017211] Bruno
```
*/

#include <iostream>
#include <stdexcept>
#include <utility>
#include <cstring>

class Aluno{
    friend std::ostream &operator<<(std::ostream &output, const Aluno &aluno){
        output << "[" << aluno.matricula << "] " << aluno.nome << "\n";
        return output;
    } 
    private:
        std::string matricula, nome;
        float media;
        int numTentativas;
    public:
        Aluno(){}
        Aluno(int numAtividades){
            int somaNotas{0}, nota, tentativa;
            
            std::cin >> this->matricula >> this->nome;

            this->numTentativas = 0;
            
            for(int j{0}; j<numAtividades; j++){
                std::cin >> nota >> tentativa;
                somaNotas+= nota;
                this->numTentativas += tentativa;
            }
            this->media = float(somaNotas)/numAtividades;
        

            
        }
        bool operator>(const Aluno &alunoB){
            if (media > alunoB.media)
                return true;
            if (media < alunoB.media)
                return false;
            if(numTentativas < alunoB.numTentativas)
                return true;
            if(numTentativas > alunoB.numTentativas)
                return false;
            return nome < alunoB.nome;
             
        }
};

typedef Aluno Dado;

class MaxHeap{

    private:
        Dado* heap;
        const unsigned int capacidade;
        unsigned int tamanho;
        int pai(int i);
        int filhoEsquerdo(int i);
        int filhoDireito(int i);
        void arruma();
        void corrigeSubindo(int i);
        void corrigeDescendo(int i);
        bool vazia();
        bool cheia();
    public:
        MaxHeap(int capacidade = 10); // construtor cria heap vazia
        MaxHeap(Dado *arr, int tamanhoArr); // construtor cria heap a partir de array já preenchido
        ~MaxHeap();
        Dado espiaRaiz();
        Dado removeRaiz();
        void insere(const Dado &d);
        void imprime(); //fins didáticos (configura quebra de estrutura)
        unsigned int getTamanho();
        unsigned int getCapacidade();
};

MaxHeap::MaxHeap(int capacidade) : capacidade(capacidade){

    heap = new Dado[capacidade];
    tamanho = 0;
}

MaxHeap::MaxHeap(Dado *arr, int tamanhoArr) : capacidade(tamanhoArr){

    tamanho = tamanhoArr;
    heap = new Dado[tamanhoArr];
    std::copy(arr, arr + tamanhoArr, heap);
    arruma();
}

MaxHeap::~MaxHeap(){
    delete[] heap;
}

void MaxHeap::arruma(){
    for(int i{int(tamanho/2 - 1)}; i>=0; i--) // metade para cima (apenas nós não-folhas) até a raiz
        corrigeDescendo(i);
}

int MaxHeap::pai(int i){
    return (i - 1)/2;
}

int MaxHeap::filhoEsquerdo(int i){
    return i*2 + 1;
}

int MaxHeap::filhoDireito(int i){
    return i*2 + 2;
}

void MaxHeap::corrigeDescendo(int i){

    int esquerdo{filhoEsquerdo(i)}, direito{filhoDireito(i)};
    int indexMaior = i;

    // verifica se algum dos filhos é maior que o pai e pega o maior em caso positivo
    if(esquerdo < int(tamanho) && heap[esquerdo] > heap[indexMaior])
        indexMaior = esquerdo;
    if(direito < int(tamanho) && heap[direito] > heap[indexMaior])
        indexMaior = direito;
    
    if(indexMaior != i){
        std::swap(heap[i], heap[indexMaior]); // troca pai com maior dos filhos
        corrigeDescendo(indexMaior); // verifica pai com seus novos filhos
    }

}

void MaxHeap::corrigeSubindo(int i){
    
    int indexPai{pai(i)};

    // verifica se o filho é maior que o pai
    if(heap[i] > heap[indexPai]){
        std::swap(heap[i], heap[indexPai]);
        corrigeSubindo(indexPai);
    }
}

bool MaxHeap::vazia(){
    return !bool(tamanho);
}

bool MaxHeap::cheia(){
    return (tamanho == capacidade);
}

Dado MaxHeap::espiaRaiz(){
    if(vazia()) 
        throw std::runtime_error("Erro: Heap Vazia.\n");
    
    return heap[0];
}

Dado MaxHeap::removeRaiz(){

    if(vazia()) 
        throw std::runtime_error("Erro: Heap Vazia.\n");
    
    Dado temp = heap[0];

    std::swap(heap[0], heap[--tamanho]);
    corrigeDescendo(0);

    return temp;
    

}

void MaxHeap::insere(const Dado &d){

    if(cheia()) 
        throw std::runtime_error("Erro: Heap Cheia.\n");
    
    heap[tamanho++] = d;
    corrigeSubindo(tamanho - 1);

}

void MaxHeap::imprime(){
    for(int i{0}; i< int(tamanho); i++)
        std::cout << heap[i] << " ";

    std::cout << "\n";
}

unsigned int MaxHeap::getTamanho(){
    return tamanho;
}

unsigned int MaxHeap::getCapacidade(){
    return capacidade;
}

int main(){

    int n, numAtividade;
    std::cin >> n >> numAtividade;

    Aluno *alunos = new Aluno[n], aluno;
    
    for(int i{0}; i<n; i++){
        aluno = Aluno(numAtividade);
        alunos[i] = aluno;
    }

    MaxHeap heap(alunos, n);

    std::cout << heap.espiaRaiz();

    delete[] alunos;

    return 0;
}