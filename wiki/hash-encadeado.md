# Colisão por Encadeamento

Confira a implementação de uma **[tabela hash com encadeamento](../src/hash/LinkedHashTable.cpp)** em C++.

## Detalhes da implementação

No tratamento de colisões por encadeamento, cada posição da tabela se trata de um ponteiro que aponta para uma lista, ou
uma lista de fato, a qual, por sua vez, armazena todos os elementos que colidiram nessa determinada posição.

Dentro de cada lista, as operações são realizadas normalmente. Detalhe para a inserção, que ocorre sempre no início para
evitar o uso desnecessário de um ponteiro para o fim.

Sendo assim, para cada operação na tabela hash, como adicionar, remover ou buscar um valor, a função hash é utilizada
para calcular o índice de acesso na tabela, e, assim, a operação de fato é efetuada na lista correspondente.
