/*
# Atendimento na fila do banco (v2)


A agência bancária decidiu contratar uma pessoa para fazer o programa que
gerencia as senhas de atendimento nos caixas expressos. Você será responsável
por essa implementação e as instruções passadas a você são: existem dois tipos
de senha, as prioritárias e as normais; as senhas são chamadas de modo a serem
chamadas 3 prioritárias para então uma normal. Não havendo prioridades, as
pessoas com senha normal podem ser atendidas normalmente. Sempre que um
atendimento normal for realizado, os próximos três devem ser prioritários, se
possível. Se estiver na hora de realizar um atendimento de cliente normal mas
não houver nenhum cliente normal, deve ser chamado um nome do atendimento
preferencial, se houver. Você deverá usar uma estrutura de dados do tipo fila e
poderá usar código fornecido.

O programa deve ler comandos representados por palavras e seus respectivos
argumentos assim:

* O comando "normal" seguido de um nome (sem espaços) representa retirada de uma
senha normal, ou seja, uma pessoa entrou na fila "normal".
* O comando "prioridade" seguido de um nome (sem espaços) representa retirada de
uma senha prioritária, ou seja, uma pessoa entrou na fila "prioridade".
* O comando "atender" representa uma senha sendo chamada.
* O comando "fim" solicita o fim da execução do programa.

Para cada comando de atendimento, o programa deverá escrever o nome da pessoa
que deve ser atendida, de acordo com as regras de atendimento vistas. Caso não
haja cliente a ser chamado, o programa deve escrever "AGUARDE" (letras
maiúsculas). A cada atendimento normal, a contagem para prioritários deve ser
reiniciada.

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

#include <exception>
#include <iostream>
#include <string>

#include "data-structure/queue/LinkedQueue.h"
#include "data-structure/queue/interface/QueueInterface.h"

typedef std::string Dado;

bool atenderFila(QueueInterface<Dado> &fila) {
  if (fila.isEmpty())
    return false;
  std::cout << fila.dequeue() << "\n";
  return true;
}

int main() {

  LinkedQueue<Dado> implNormal, implPrioritario;
  QueueInterface<Dado> &filaNormal = implNormal,
                       &filaPrioritario = implPrioritario;
  Dado d;
  std::string opcao, nome;
  int atendimentosRestantes{3};
  bool atendeu;

  do {

    try {

      std::cin >> opcao;

      if (opcao == "normal") {

        std::cin >> nome;
        filaNormal.queue(nome);
      } else if (opcao == "prioridade") {
        std::cin >> nome;
        filaPrioritario.queue(nome);
      } else if (opcao == "atender") {

        atendeu = true;

        if (atendimentosRestantes > 0) {
          atendeu = atenderFila(filaPrioritario);

          if (!atendeu) {
            atendeu = atenderFila(filaNormal);
            if (atendeu)
              atendimentosRestantes = 3;
          } else {
            atendimentosRestantes--;
          }
        } else {
          atendeu = atenderFila(filaNormal);

          if (!atendeu) {
            atendeu = atenderFila(filaPrioritario);
          } else {
            atendimentosRestantes = 3;
          }
        }

        if (!atendeu)
          std::cout << "AGUARDE\n";
      }

    } catch (std::exception &err) {
      std::cout << err.what() << "\n";
    }

  } while (opcao != "fim");

  return 0;
}
