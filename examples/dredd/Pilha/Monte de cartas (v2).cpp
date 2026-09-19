/*
# Monte de cartas (v2)


Giovani decidiu ordenar sua grande coleção de cartas de "Yu-Gi-Oh!". Para isso pediu sua ajuda e lhe informou que queria um monte ordenado em ordem crescente pelo poder das cartas, e não teria cartas repetidas. Como tinha muitas, ele decidiu ordenar dois montes em ordem crescente (podendo conter cartas repetidas). Sua missão agora é ajudar Giovani a unir os dois montes retirando suas cartas repetidas. Utilizando-se da estrutura da dado fila, faça um programa que lê duas filas já em ordem crescente e cria uma terceira fila com os valores das duas primeiras em ordem crescente sem que haja repetição de elementos.

Não é permitido utilizar a STL ou similares para resolver o problema, bem como acessar os dados desrespeitando as propriedades da estrutura.

### Entradas

```
1. Quantidade de elementos da fila 1.
2. Elementos da fila 1 em ordem crescente.
3. Quantidade de elementos da fila 2.
4. Elementos da fila 2 em ordem crescente.
```

### Saídas

```
1. Elementos da fila de resultados.
```

### Exemplo de Entrada

```
7
1 3 5 7 10 10 11
6
2 4 6 8 10 12
```

### Exemplo de Saída

```
1 2 3 4 5 6 7 8 10 11 12
```
*/

#include <iostream>
#include <stdexcept>

typedef int Dado;

class Noh{

    //permitir acesso da queue aos atributos privados do Noh
    friend class FilaEncadeada;

    // noh armazena dado e ponteiro para o próximo
    private:
        Noh* proximo;
        Dado dado;
    public:
        Noh(const Dado &d) : dado(d), proximo(nullptr) {}
};

class FilaEncadeada{
    private:
        Noh *inicio, *fim;
        unsigned int tamanho;
    public:
        FilaEncadeada();
        ~FilaEncadeada();
        void enfileira(const Dado &d);
        Dado desenfileira();
        void limparTudo();
        unsigned int getTamanho();
        bool vazia();
        Dado espiarInicio();
};

FilaEncadeada::FilaEncadeada(){
    inicio = fim = nullptr;
    tamanho = 0;
}

FilaEncadeada::~FilaEncadeada(){
    limparTudo();
}

void FilaEncadeada::limparTudo(){
    while(!vazia())
        desenfileira();
}

void FilaEncadeada::enfileira(const Dado &d){

    Noh *novo = new Noh(d);

    if(vazia())
        inicio = novo;
    else
        fim->proximo = novo; // proximo do antigo fim é novo
    
    fim = novo; // fim passa a ser o novo elemento

    tamanho++;

}

Dado FilaEncadeada::desenfileira(){

    if(vazia())
        throw std::runtime_error("Erro: Fila Vazia!");

    Noh *aux = inicio;
    Dado temp = inicio->dado;

    inicio = inicio->proximo;
    delete aux;
    tamanho--;

    if(vazia())
        fim = nullptr;

    return temp;

}

unsigned int FilaEncadeada::getTamanho(){
    return tamanho;
}

bool FilaEncadeada::vazia(){
    return !bool(inicio);
}

Dado FilaEncadeada::espiarInicio(){

    if(vazia())
        throw std::runtime_error("Erro: Fila Vazia!");

    return inicio->dado;
}

void leituraFila(int tam, FilaEncadeada &fila){

    int n;

    for(int i{0}; i<tam; i++){
        std::cin >> n;
        fila.enfileira(n);
    }    

}

void ordenaMonte(FilaEncadeada &filaA, FilaEncadeada &filaB, FilaEncadeada &filaC){

    int numA, numB, ultimoEnfifeirado;
    FilaEncadeada *filaMenor;

    while(!filaA.vazia() && !filaB.vazia()){ 
        
        filaMenor = (filaA.espiarInicio() <= filaB.espiarInicio()) ? &filaA : &filaB;

        if(!filaC.getTamanho() || filaMenor->espiarInicio() != ultimoEnfifeirado){
            ultimoEnfifeirado = filaMenor->desenfileira();
            filaC.enfileira(ultimoEnfifeirado);
        }else
            filaMenor->desenfileira();
    }

    while(!filaA.vazia()){ 
        
        if(!filaC.getTamanho() || filaA.espiarInicio() != ultimoEnfifeirado){
            ultimoEnfifeirado = filaA.desenfileira();
            filaC.enfileira(ultimoEnfifeirado);
        }else
            filaA.desenfileira();
    }

    while(!filaB.vazia()){ 
        
        if(!filaC.getTamanho() || filaB.espiarInicio() != ultimoEnfifeirado){
            ultimoEnfifeirado = filaB.desenfileira();
            filaC.enfileira(ultimoEnfifeirado);
        }else
            filaB.desenfileira();
    }

}

int main(){

    FilaEncadeada filaA, filaB, filaC;
    int tam;

    std::cin >> tam;
    leituraFila(tam, filaA);

    std::cin >> tam;
    leituraFila(tam, filaB);

    ordenaMonte(filaA, filaB, filaC);

    while(!filaC.vazia())
        std::cout << filaC.desenfileira() << " "; 


    return 0;
}