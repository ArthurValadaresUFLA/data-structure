/*
# Atendimento na fila do banco (v2)


A agência bancária decidiu contratar uma pessoa para fazer o programa que gerencia as senhas de atendimento nos caixas expressos. Você será responsável por essa implementação e as instruções passadas a você são: existem dois tipos de senha, as prioritárias e as normais; as senhas são chamadas de modo a serem chamadas 3 prioritárias para então uma normal. Não havendo prioridades, as pessoas com senha normal podem ser atendidas normalmente. Sempre que um atendimento normal for realizado, os próximos três devem ser prioritários, se possível. Se estiver na hora de realizar um atendimento de cliente normal mas não houver nenhum cliente normal, deve ser chamado um nome do atendimento preferencial, se houver. Você deverá usar uma estrutura de dados do tipo fila e poderá usar código fornecido.

O programa deve ler comandos representados por palavras e seus respectivos argumentos assim:

* O comando "normal" seguido de um nome (sem espaços) representa retirada de uma senha normal, ou seja, uma pessoa entrou na fila "normal".
* O comando "prioridade" seguido de um nome (sem espaços) representa retirada de uma senha prioritária, ou seja, uma pessoa entrou na fila "prioridade".
* O comando "atender" representa uma senha sendo chamada.
* O comando "fim" solicita o fim da execução do programa.

Para cada comando de atendimento, o programa deverá escrever o nome da pessoa que deve ser atendida, de acordo com as regras de atendimento vistas. Caso não haja cliente a ser chamado, o programa deve escrever "AGUARDE" (letras maiúsculas). A cada atendimento normal, a contagem para prioritários deve ser reiniciada.

### Entradas

```
1. Sequência de comandos, seguindo as instruções acima.
```

### Saídas

```
1. Somente o comando "atender" gera saída, conforme instruções acima.
```

### Exemplo de Entrada

```
normal Abner
prioridade Ackson
normal Adilson
normal Adriana
normal Adriano
normal Adriel
prioridade Adrielle
atender
atender
atender
atender
prioridade Adriene
prioridade Adson
prioridade Afonso
prioridade Agatha
atender
atender
atender
atender
atender
fim
```

### Exemplo de Saída

```
Ackson
Adrielle
Abner
Adilson
Adriene
Adson
Afonso
Adriana
Agatha
```
*/

#include <iostream>
#include <stdexcept>

typedef std::string Dado;

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
        std::string getTipoFila();
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

bool atenderFila(FilaEncadeada &fila){
    if(fila.vazia())
        return false;
    std::cout << fila.desenfileira() << "\n";
    return true;
}

int main(){

    FilaEncadeada filaNormal, filaPrioritario;
    Dado d;
    std::string opcao, nome;
    int atendimentosRestantes{3};
    bool atendeu;

    do{

        try{

            std::cin >> opcao;

            if(opcao == "normal"){

                std::cin >> nome;
                filaNormal.enfileira(nome);
            }else if(opcao == "prioridade"){
                std::cin >> nome;
                filaPrioritario.enfileira(nome);
            }else if(opcao == "atender"){

                atendeu = true;

                if(atendimentosRestantes > 0){
                    atendeu = atenderFila(filaPrioritario);

                    if(!atendeu){
                        atendeu = atenderFila(filaNormal);
                        if(atendeu)
                            atendimentosRestantes = 3;
                    }else{
                        atendimentosRestantes--;
                    }
                }else{
                    atendeu = atenderFila(filaNormal);

                    if(!atendeu){
                        atendeu = atenderFila(filaPrioritario);
                    }else{
                        atendimentosRestantes = 3;
                    }
                }

                if(!atendeu)
                    std::cout << "AGUARDE\n";

            }

        }catch(std::runtime_error &err){
            std::cout << err.what() << "\n";
        }

    }while(opcao != "fim");

    return 0;
}