# Pilhas

## Tópicos

- Definição;
- Tipos de Pilhas:
    - Encadeada;
    - Em arranjo;
- Implementações;

## Definição e Visão Geral

### O que é?

**Pilhas** são estruturas de dados nas quais os elementos pertencentes são ordenados de forma que o último elemento a
ser inserido se posiciona como o primeiro a ser retirado - política do Fist-In-Last-Out, FILO -, tendo em vista que a
definição de pilha restringe que as inserções e remoções - denominadas como 'push' e 'pop' na literatura -, sejam feitas
pelo topo.

A fim de facilitar o entendimento, podemos fazer uma analogia com uma pilha de livros, por exemplo. A medida com que
você vai estudar, fazendo a leitura das referências bibliográficas referentes à matéria em questão, você acaba
dispondo os livros lidos numa pilha, um em cima do outro. Em certo momento, o livro que lê referencia um que você já leu
e que está na pilha, nesse caso, por não se lembrar especificamnte do trecho, você precisa reler, para tal, tens de
retirar cada livro que esta acima do requerido. Você não pode retirar os livros por baixo da pilha, pelo lado... corre o
risco de derubar tudo, retirar pelo _lado_ é uma quebra do encapsulamento da estrutura de dados.

## Tipos de Pilhas

No que tange à implementação de pilhas, há dois tipos principais abordados durante o curso:

- Pilha em Arranjo;
- Pilha Encadeada;

A baixo segue a diferença entre elas, aplicações, vantagens e desvantagens.

### Pilhas em Arranjo

Pilhas em arranjo se assemelham muito às [filas em arranjo](./Fila.md#filas-em-arranjo), excluso que se trata de apenas
uma entrada e saída, isto é, há duas variáveis numa pilha em arranjo: o vetor alocado dinamicamente e um atributo
indicando o topo. A medida com que os elementos são inseridos na pilha o topo é incrementado, analogamente, quando os
elementos são retirados, o topo é decrementado. Se na pilha, denotada por _P_, o topo igualar o tamanho, isto é,
_P.topo_ = _P.tamanho_, a pila está cheia, ao passo que, se _P.topo_ = 1 a pilha está vazia.

### Pilhas Encadeadas

As pilhas encadeadas contêm um atributo - em algus casos, 2 -, são eles: o ponteiro apontando para o fim do encadeamento
e, opcionalmente, a quantidade de elementos na pilha. Uma pilha pode ser duplamente encadeada ou unicamente encadeada,
isso diz respeito aos atributos de cada um dos nós contidos numa pilha, isto é, os elos que constituem a corrente - a
pilha em si, nessa analogia. Um nó duplamente encadreado é aquele que tanto armazena um ponteiro indicando o próximo nó
quanto para o nó predescessor, ao passo que o nó unicamente encadeado indica somente o nó subsequente.

O atributo que indica o tamanho da pilha tem de ser atualizado a cada inserção ou remoção, a fim de manter a
consistência com os elementos preentes na pilha. Se o ponteiro que aponta para o fim da pilha é nulo, a pilha está
vazia, se não, há dados dentro dela.

No processo de inserção de elementos numa pilha, o valor a ser inserido deve ser encapsulado e seu antecessor deve ser
definido como aquele que, até então, estava no topo, e, caso seja uma pilha duplamente encadadeda, deve-se definir o
suscessor do topo o novo nó criado, feito isso é necessário atualizar o ponteiro que aponta para o topo, passando a
indicar o novo nó.

O processo de remoção é análogo: o ponteiro para o topo aponta para aquele que está abaixo, a referência para o nó que
estava no topo é modificada para ser nulo naquele que estáva abaixo dele, o valor é desencapsulado do nó removido e o nó
é deletado da memória.

## Implementações

Confira a implementação de uma Pilha Duplamente Encadeada [aqui](../src/stack/LinkedStack.cpp) e o seu respectivo
arquivo
de [cabeçalho](../include/stack/LinkedStack.h).

Confira a implementação de uma Pilha em Arranjo [aqui](../src/stack/ArrayStack.cpp) e o seu respectivo arquivo
de [cabeçalho](../include/stack/ArrayStack.h).

[//]: # (### Aplicações)