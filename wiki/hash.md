# Tabelas Hash

## Tópicos

* [Colisão por Encadeamento](../src/hash/linked)
* [Colisão por Endereçamento Aberto](../src/hash/open_address)

## Definição e Visão Geral

### O que é?

**Tabela Hash** é uma estrutura de dados que, num caso ideal, por meio de uma **função hash**, a qual associa para uma
determinada **chave** um **índice no _array**, permite a busca por elementos em ordem constante $0(1)$ (**acesso direto à
posição**).

Essa maior eficiência na busca é acompanhada de **maior uso de memória**, visto que a estrutura se descaracteriza com
ocupação acima de 75% (o tratamento de colisões se torna demasiadamente custoso).

A função de hash mais básica utilizada é o cálculo do **mod da chave em relação ao tamanho do _array**, que retorna
sempre um valor entre 0 e (tamanho - 1), o qual é utilizado como índice de acesso no _array.

Como dito anteriormente, uma tabela hash começa a se tornar ineficiente quando a sua taxa de ocupação ultrapassa 75%. Sendo
assim, algumas abordagens utilizam o redimensionamento da estrutura quando esse valor crítico é atingido. Essa técnica é
chamada de **tabela hash dinâmica**.

Existe a suposição de que uma boa função hash consegue distribuir cada chave numa posição diferente da tabela,
independentemente das posições que as demais chaves foram atribuídas. No entanto, esse se trata de um cenário muito
ideal e, por mais eficiente que a função hash utilizada seja, é necessário que a tabela hash detenha de mecanismos para
tratamento de colisões.

Colisão é o fenómeno quando duas chaves são associadas ao mesmo endereço na tabela. Para contornar esse problema duas
técnicas são normalmente utilizadas: tratamento de **[colisão por encadeamento](../src/hash/linked)** e por 
**[endereçamento aberto](../src/hash/open_address)**.

[//]: # (### Aplicações)

## Confira

- [Hash por encadeado](./Hash%20Encadeado.md)
- [Hash com enderreçamento aberto](./Hash%20com%20Endereco%20Aberto.md)