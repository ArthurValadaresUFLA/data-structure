# Torneios

Confira a implementação de um [Torneio](../src/heap/tournament/torneio.cpp) em C++.

## Detalhes da implementação

A implementação de um **torneio** se assemelha muito a implementação de um heap, com a diferença já citada
anteriormente: **cada pai contém uma cópia do maior entre seus dois filhos**. Dessa forma, **o conteúdo dos nós folhas
determina todos os valores restantes da árvore**.

Geralmente, torneios são implementados para a **obtenção de um vencedor**. Dessa forma, para a maioria das
implementações não faz sentido a operação de **remoção**. O mais sensato a se fazer, caso haja essa opção, seria *
*refazer o torneio com os elementos restantes**.

No caso de **torneios incompletos**, em que o **número de elementos não é uma potência de 2**, algumas **posições
intermediárias** são preenchidas como **inválidas**.

Dessa forma, o **número de nós intermediários** é dado pela **primeira potência de 2 que seja maior ou igual o número de
dados decrescido de uma unidade**.