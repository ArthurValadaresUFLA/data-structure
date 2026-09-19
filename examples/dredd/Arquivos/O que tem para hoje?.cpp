/*
# Arquivo Tipado - O que tem para hoje?


Faça um programa que leia tarefas de um arquivo tipado, leia uma data representando a data de hoje e escreva quais as tarefas que devem ser feitas na data indicada

Para encurtar o desenvolvimento do programa, o programa pode ser feito supondo o arquivo tipado já existe e já tem as informações nele. Para testar o seu programa, você pode usar o **[arquivo de exemplo](o-que-tem-para-hoje)**. Não mude o nome do arquivo.

A comparação entre datas deve ser feita numa sub-rotina específica para isto. Um bom planejamento dos parâmetros é parte da avaliação.

O arquivo com tarefas tem o seguinte formato:

1. Um número inteiro sem sinal, representando o número de registros do arquivo.
1. Vários registros que representam tarefas.

Cada tarefa é representada por:

1. uma descrição (sequência de caracteres - 40 bytes);
2. uma data.

Cada data é representa por 3 inteiros sem sinal, respectivamente o dia, mês e ano.

### Entradas

```
1. dia, mês e ano que representam a data de hoje.
```

### Saídas

```
1. Todas as tarefas do arquivo com a data de hoje.
```

### Exemplo de Entrada

```
17 12 2014
```

### Exemplo de Saída [(em conjunto com o arquivo de exemplo)](o-que-tem-para-hoje)

```
Estudar arquivos tipados.
```
*/

#include <iostream>
#include <fstream>

struct Data{
    int dia, mes, ano;
};

struct Tarefa{
    char descricao[40];
    Data dataTarefa;
};

bool datasIguais(const Data &dataA,const Data &dataB){
    return (dataA.dia == dataB.dia && dataA.mes == dataB.mes && dataA.ano == dataB.ano);
}

int main(){

    std::string nomeArq{"o-que-tem-para-hoje"};
    std::ifstream arq(nomeArq);

    int numTarefas;
    arq.read((char *) (&numTarefas), sizeof(int));

    Data dataAtual;
    std::cin >> dataAtual.dia >> dataAtual.mes >> dataAtual.ano;

    Tarefa tarefa;

    for(int i{0}; i<numTarefas; i++){
        arq.read((char *) (&tarefa), sizeof(Tarefa));
        if(datasIguais(dataAtual, tarefa.dataTarefa))
            std::cout << tarefa.descricao << "\n";
    }

    return 0;
}