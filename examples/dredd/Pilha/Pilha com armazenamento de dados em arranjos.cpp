/*
# Pilha com armazenamento de dados em arranjos 


Implemente uma pilha, utilizando armazenamento dos dados em arranjos (vetores). Segue esboço da implementação:

```
typedef int Dado; // para facilitar a troca de int para outro tipo
 
// pilha implementada em arranjo 
class pilhav {
    private:
        int capacidade;
        Dado *dados;
        int tamanho;
        int posTopo;
    public:
        pilhav(int cap = 100);
        ~pilhav();
        void empilha(Dado valor);
        Dado desempilha();
        Dado espia(); // acessa elemento do topo, mas não retira
        void depura(); // imprime os dados do vetor da pilha sem removê-los (desempilhar)
        void info();  // imprime informações da pilha (tamanho e  posição do topo)
};
```

Não é necessário tratar problemas do tipo retirada de elemento de pilha vazia ou empilhamento em pilha cheia. A aplicação principal deverá criar uma pilha com capacidade para 20 elementos e realizar as seguintes operações na ordem apresentada:

1. Empilhar cinco elementos
1. Desempilhar três elementos (imprimindo-os)
1. Empilhar mais quatro elementos
1. Desempilhar três elementos (imprimindo-os)
1. Imprime o topo da pilha, sem desempilhar (espia())
1. Imprime os elementos restantes da pilha (depura())
1. Imprime tamanho e posição do topo (info())

### Entradas

```
1. Cinco valores a serem empilhados
2. Quatro valores a serem empilhados
```

### Saídas

```
1. Três elementos desempilhados
2. Três elementos desempilhados
3. Topo da pilha
4. Elementos restantes da pilha
5. Tamanho e posição do topo
```

### Exemplo de Entrada

```
8 9 1 3 5
12 23 0 3
```

### Exemplo de Saída

```
5 3 1
3 0 23
12
8 9 12
3 2
```
*/

#include <iostream>

typedef int Dado; // para facilitar a troca de int para outro tipo
 
// stack implementada em arranjo
class pilhav {
    private:
        int capacidade;
        Dado *dados;
        int tamanho;
        int posTopo;
    public:
        pilhav(int cap = 100);
        ~pilhav();
        void empilha(const Dado &valor);
        Dado desempilha();
        Dado espia(); // acessa elemento do topo, mas não retira
        void depura(); // imprime os dados do vetor da stack sem removê-los (desempilhar)
        void info();  // imprime informações da stack (tamanho e  posição do topo)
};

pilhav::pilhav(int cap){

    tamanho = 0;
    posTopo = -1;
    capacidade = cap;

    dados = new Dado[cap];

}

pilhav::~pilhav(){
    delete[] dados;
}

void pilhav::empilha(const Dado &valor){

    dados[++posTopo] = valor;
    tamanho++;
}

Dado pilhav::desempilha(){
    tamanho--;
    return dados[posTopo--];
}

Dado pilhav::espia(){
    return dados[posTopo];
}

void pilhav::depura(){
    for(int i{0}; i<tamanho; i++){
        std::cout << dados[i] << " ";
    }
    std::cout << "\n";
}

void pilhav::info(){
    std::cout << tamanho << " " << posTopo << "\n";
}

int main(){

    pilhav pilhaArr(20);
    Dado d;

    for(int i{0}; i<5; i++){
        std::cin >> d;
        pilhaArr.empilha(d);
    }
    for(int i{0}; i<3; i++){
        std::cout << pilhaArr.desempilha() << " ";
    }
    std::cout << "\n";

    for(int i{0}; i<4; i++){
        std::cin >> d;
        pilhaArr.empilha(d);
    }
    for(int i{0}; i<3; i++){
        std::cout << pilhaArr.desempilha() << " ";
    }
    std::cout << "\n";

    std::cout << pilhaArr.espia() << "\n";
    pilhaArr.depura();
    pilhaArr.info();

    return 0;
}