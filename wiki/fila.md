# Filas

## Tópicos

- Definição de fila;
- Tipos de fila:
    - Arranjo:
        - Linear;
        - Circular;
    - Encadeamento

## Definição e Visão Geral

### O que é?

**Filas** são estruturas de dados nas quais os elementos existentes são ordenados conforme o momento de entrada,
mantendo sempre a mesma ordem, seguindo, portanto, uma _política_ FIFO, um acrónimo em inglês para First-In First-Out,
ou seja, o primeiro a entrar é o primeiro a sair.
É importante destacar que existem filas nas quais fatores diferentes dos relacionados ao momento de entrada são
considerados, a exemplo de filas prioritárias. Apesar do que pode parecer, filas prioritárias não ferem o
_encapsulamento_, visto que os dados são somente acessíveis pelos métodos apropriados.

Filas possuem dois métodos característicos: Enqueue, enfileirar, e
Dequeue, desenfileirar. Consistem basicamente em: remover um elemento no início e adicionar um elemento no final,
respectivamente. A fim de auxiliar a compreensão, uma fila não só se assemelha como, conforme a definição, pode ser
exemplificada como à experienciada em, por exemplo, um banco ou supermercado. Onde uma pessoa, mediante o momento de
entrada na fila, adquire uma posição que vai sendo decrementado conforme a chamada dos indivíduos se de posições
inferiores, isto é, a medida com que as pessoas são desenfileiradas.

Uma dúvida surge, por exemplo, ao analisar um guichê de hospital: geralmente, você passa por uma
sondagem que possui uma fila simples, ao passar por essa sondagem você é encaminhado para um setor no qual há uma fila,
muito provavelmente, prioritária, na qual o atendimento das pessoas considera a idade, o grupo de risco, o plano de
saúde a urgência e tempo de espera total, isso constitui uma fila prioritária. Não se preocupe com isso, no momento,
foge ao escopo do curso.

## Tipos de filas

No que tange à implementação de filas, há dois tipos principais abordados ao longo do curso:

- Encadeada;
- Em arranjo;

A baixo segue a diferença entre elas, aplicações, vantagens e desvantagens.

### Filas Encadeadas

Filas encadeadas constituem numa estrutura de dados cujos elementos são encapsulados em classes que representam _nós_, o
conjunto de _nós_ forma uma fila, desde que siga a _política_ **FIFO**. A fim de auxiliar a compreensão, uma fila e os
seus respectivos nós podem ser entendidos como uma corrente, isto é, cada elemento de uma corrente, cada elo, constitui
num nó, ao passo que o conjunto de nós encadeados, ou seja, a corrente, é entendida como a fila em si. A fim de ter
acesso a cada ele da corrente é necessário tê-la, isto é, segurá-la por algum ponto: pelo início, fim ou ambos.

A fim de acelerar o processo de inserção e remoção - leia-se: enfileiramento e desenfileiramento - armazena-se uma
referência para ambas as extremidades a fim de diminuir o tempo necessário os métodos característicos e, mui
provavelmente, os mais utilizados.

Uma fila encadeada, assim como, por exemplo, uma lista ou pilha, pode ter nós singular ou duplamente encadeados,
isto é, armazenar tanto uma referência para o nó subsequente quanto para o nó precedente. No processo de inserção de um
elemento, logicamente, no final da lista, se o ponteiro para o último nó é nulo, assim como o ponteiro para o primeiro
nó, a lista está vazia, e o valor a ser adicionado tem de ser encapsulado num nó e,
quando o for, tanto será o objeto apontado pelo ponteiro de início quanto o de fim, se o ponteiro para o fim e início
não apontam para nulo o último nó tem que apontar para o novo nó criado - aquele que encapsula o elemento - como o seu
subsequente, ademais, se o nó for duplamente encadeado, o novo nó deve apontar para o último como sendo o seu
predecessor. O ponteiro para o último deve ser atualizado, apontando agora para o novo nó, devidamente encadeado. Se o
ponteiro para o primeiro
elemento ou o último apontar para nulo e o outro não, há uma inconsistência na fila.

No processo de remoção de um elemento de uma fila, o primeiro elemento é acessado por meio do ponteiro de início, se os
nós forem duplamente encadeados, o subsequente ao primeiro, se existir, deverá ter definido como o seu precedente o
valor nulo. O ponteiro de início deve passar a apontar para o subsequente daquele que, até então, era o primeiro, o
valor dese ser desencapsulado, ouse aja, retirado do nó, o nó deve ser deletado e o valor retornado. Se o primeiro for
também o último, ao ser removido, ambos os ponteiros, de início e fim, devem apontar para nulo.

### Filas em Arranjo

#### Arranjo Linear

Uma fila pode ser disposta ao longo de um vetor dinamicamente alocado, a fila então passa a ter, no mínimo, três
atributos: o ponteiro do vetor dinamicamente alocado, o início e o fim da fila. A medida que os elementos são
enfileirados, o fim se desloca para a direita e, analogamente, à medida que os elementos são desenfileirados o
início se desloca também para a direita. Como a fila não é circular - veremos a definição mais adiante -, quando o
atributo _fim_ da fila, denotada por _Q_, se iguala ao tamanho, isto é, _Q.fim_ = _Q.tamanho_, a fila está cheia,
nenhum elemento pode ser adicionado a ele sem que seja necessário fazer um processo de realocação de memória para um
vetor de tamanho igual ou menor, removendo aqueles que precedem o início, ou maior. Se o início iguala o fim, a fila
está vazia, se não, a fila tem, pelo menos, um elemento. É importante destacar que, no contexto de arranjo, os atributos
de início e de fim podem ser tanto inteiros indicando as índices quanto vetores apontando para os endereços de memória.

Uma fila em arranjo pode ter um atributo opcional: tamanho, usado para armazenar a quantidade de elementos presentes na
fila, deve ser manutenida, isto é, o seu valor deve ser alterado conforme faz-se inserções e remoções na fila,
incrementando e decrementando respectivamente.

#### Arranjo Circular

Um arranjo circular se assemelha muito ao linear, excluso que, quando o fim se iguala ao tamanho, ao ser incrementado,
ele volta para o início - use-se o _(mod n)_ para tal -, adicionando mais algumas restrições tais quais: a fila _não
completou uma volta_, logo, se _Q.fim_ = _Q.tamanho_ e _Q.incio_ = 1 - a posição inicial na literatura -, a fila está
cheia. Entretanto, se a fila já _completou uma volta_, se _Q.inicio_ = _Q.fim_ + 1, a fila está cheia.

## Vantagens e desvantagens

### Arranjo

- Leitura e escrita mais rápidas;
- Tamanho limitado e de aumento computacionalmente custoso;
- Gestão mais fácil;
- O tempo de leitura de um elemento é constante;

### Encadeamento

- Leitura e escrita mais lenta;
- Tamanho limitado somente pela quantidade de memória alocada ao programa;
- Mais difícil de ser gerenciada;
- Tempo de leitura de um elemento é linear, isto é, para ler o 3.º elemento é necessário ler todos que o precedem
  ou suscedem, mediante o ponto de escolha para o início da iteração: início ou fim da fila;

## Implementação:

Confira a implementação de uma fila duplamanete encadeada [aqui](../src/queue/LinkedQueue.cpp) e o seu respectivo
arquivo de [cabeçalho](../include/queue/LinkedQueue.h).

Confira a implementação de uma fila circular em arranjo [aqui](../src/queue/ArrayQueue.cpp) e o seu respectivo arquivo
de [cabeçalho](../include/queue/ArrayQueue.h)

[//]: # (#### Arranjo Circular)

[//]: # (### Aplicações)

[//]: # (TODO:)

[//]: # ()

[//]: # (- Talvez adicionar o contexto de fila de prioridades, retratando o funcionamento de, por exemplo, um caixa preferencial,)

[//]: # (  a fila de um caixa, fila de reservas virtuais, execução de atividades num sistema operacional)
