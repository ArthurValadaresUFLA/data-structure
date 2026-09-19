# Listas

## Tópicos

- Definição

## Definição e Visão Geral

### O que é?

Listas são estruturas de dados nas quais as informações são armazenadas de forma linear, em objetos constituintes
denominados frequentemente de **nós**. Como elos numa corrente, eles constituem listas, as listas podem adquirir
diversas formas dentre as quais, conforme restrições impostas pelo encapsulamento,
estão: [Fila Encadeada](./Fila.md#filas-encadeadas) e [Pilha Encadeada](./Pilha.md#pilhas-encadeadas).

Há dois tipos de listas, no que tange a estrutura de cada um dos nós constituintes:

- Simplesmente encadeada;
- Duplamente encadeada;

Um nó simplesmente encadeado é aquele que, além do dado e de informações _satélites_, possui um ponteiro apontando para
o próximo elemento; ao passo que nós duplamente encadeados são aqueles que tanto têm um ponteiro para o próximo elemento
quanto para o antecessor. Se o ponteiro para o anterior é nulo, o elemento é o primeiro da lista. Se o ponteiro para o
próximo é nulo, ele é o último da lista.

O processo de inserção, busca e remoção depende da abordagem adotada, a inserção no início e,
se houver um ponteiro para o fim da mesma forma que há para início, tem tempo de execução constante, isto é, O(1). Para
a inserção numa posição _k_ qualquer, a complexidade é linear no pior dos cenários, O(n), isto é, no pior dos casos tem
de se verificar cada um dos elementos da lista antes de fazer a inserção.

Tendo em vista que, da mesma forma que a inserção, na remoção é necessário percorrer, no pior dos
casos, toda a lista a fim de achar o nó cujo valor armazenado corresponde àquele que deve ser removido, a complexidade,
portanto também é O(n).

É importante destacar que apesar da remoção e inserção terem complexidade O(n) o que, em fato, _atrasa_ a inserção,
remoção é achar o elemento, visto que o processo de inserir ou remover, excluso a busca do elemento na posição, ou com a
chave específica, é constante, isto é O(1), visto que basta alterar os ponteiros para o próximo e, se for o caso,
para o anterior, seguido da desalocação do nó que contém a chave a ser deletada.

## Implementações

Confira:

- Lista Duplamente Encadeada: [implementação](../src/list/DoublyLinkedList.cpp)
  e [cabeçalho](../include/list/DoublyLinkedList.h);
- Lista Simplesmente Encadeda: [implementação](../src/list/SinglyLinkedList.cpp)
  e [cabeçalho](../include/list/DoublyLinkedList.h);

[//]: # (### Aplicações)