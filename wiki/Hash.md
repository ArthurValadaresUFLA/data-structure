# Tabelas Hash

## O que é?

**Tabela Hash** é uma estrutura de dados que, num caso ideal, por meio de uma **função hash** — a qual associa a uma
determinada **chave** um **índice no array** —, permite a busca por elementos em tempo constante, $O(1)$ (**acesso
direto à posição**).

Essa maior eficiência na busca é acompanhada de **maior uso de memória**, visto que a estrutura se descaracteriza com
ocupação acima de 75% (o tratamento de colisões se torna demasiadamente custoso).

A função de hash mais básica utilizada é o cálculo do **mod da chave em relação ao tamanho do array**, que retorna
sempre um valor entre 0 e (tamanho - 1), o qual é utilizado como índice de acesso no array:

```cpp
int hash(int chave, int tamanhoTabela) {
    return chave % tamanhoTabela;
}
```

Como dito anteriormente, uma tabela hash começa a se tornar ineficiente quando a sua taxa de ocupação, conhecida
como **fator de carga** ($\alpha = n / \text{tamanho}$, onde *n* é o número de elementos armazenados), ultrapassa
75%. Sendo assim, algumas abordagens utilizam o redimensionamento da estrutura quando esse valor crítico é atingido.
Essa técnica é chamada de **tabela hash dinâmica**.

Existe a suposição de que uma boa função hash consegue distribuir cada chave numa posição diferente da tabela,
independentemente das posições que as demais chaves ocupam. No entanto, esse é um cenário muito ideal e, por mais
eficiente que a função hash utilizada seja, é necessário que a tabela hash disponha de mecanismos para tratamento de
colisões.

**Colisão** é o fenômeno que ocorre quando duas chaves são associadas ao mesmo endereço na tabela. Para contornar
esse problema, duas técnicas são normalmente utilizadas: tratamento de colisão por encadeamento e por endereçamento
aberto.

## Tipos de Tabelas Hash

No escopo do curso, há dois tipos de tabelas hash, que fazem uso de:

- Colisão por Encadeamento;
- Colisão por Endereçamento Aberto;

## Colisão por Encadeamento

No tratamento de colisões por encadeamento, cada posição da tabela armazena uma lista (encadeada, por exemplo), a
qual, por sua vez, guarda todos os elementos cuja chave colidiu naquela determinada posição.

```cpp
#include <vector>
#include <list>

struct TabelaHashEncadeada {
    std::vector<std::list<int>> tabela;

    TabelaHashEncadeada(int tamanho) : tabela(tamanho) {}
};

int hash(int chave, int tamanhoTabela) {
    return chave % tamanhoTabela;
}

void inserir(TabelaHashEncadeada& t, int chave) {
    int indice = hash(chave, t.tabela.size());
    t.tabela[indice].push_front(chave); // inserção sempre no início da lista
}

bool buscar(TabelaHashEncadeada& t, int chave) {
    int indice = hash(chave, t.tabela.size());

    for (int valor : t.tabela[indice]) {
        if (valor == chave) return true;
    }

    return false;
}

void remover(TabelaHashEncadeada& t, int chave) {
    int indice = hash(chave, t.tabela.size());
    t.tabela[indice].remove(chave);
}
```

Dentro de cada lista, as operações são realizadas normalmente. Destaque para a inserção, que ocorre sempre no início
para evitar o uso desnecessário de um ponteiro para o fim.

Sendo assim, para cada operação na tabela hash, como adicionar, remover ou buscar um valor, a função hash é utilizada
para calcular o índice de acesso na tabela, e, então, a operação de fato é efetuada na lista correspondente a esse
índice.

## Colisão por Endereçamento Aberto

No tratamento de colisão por endereçamento aberto, sempre que há a tentativa de inserção numa posição já ocupada,
procura-se a próxima posição disponível para armazenar o novo elemento — estratégia conhecida como **sondagem linear**
quando essa busca é feita percorrendo as posições subsequentes uma a uma.

```cpp
struct TabelaHashAberta {
    static const int VAZIO = -1;
    std::vector<int> tabela;

    TabelaHashAberta(int tamanho) : tabela(tamanho, VAZIO) {}
};

int hash(int chave, int tamanhoTabela) {
    return chave % tamanhoTabela;
}

void inserir(TabelaHashAberta& t, int chave) {
    int indice = hash(chave, t.tabela.size());

    while (t.tabela[indice] != TabelaHashAberta::VAZIO) {
        indice = (indice + 1) % t.tabela.size(); // sondagem linear
    }

    t.tabela[indice] = chave;
}
```

Essa estratégia exige alterações na maneira de fazer a busca e a remoção de um determinado elemento.

Durante a busca, ao mapear uma determinada chave para uma posição, o elemento lá armazenado pode não ser o elemento
que se procura; é necessário, então, percorrer todas as posições subsequentes (array circular) até que se encontre o
elemento, uma posição vazia, ou, então, até que se retorne à posição inicial da busca. Isso se deve ao fato de que,
ao não inserir um dado elemento na sua posição "correta" (calculada pela função hash), não há como garantir se ele se
encontra na tabela ou não até que as posições subsequentes sejam verificadas.

```cpp
bool buscar(TabelaHashAberta& t, int chave) {
    int indice = hash(chave, t.tabela.size());
    int indiceInicial = indice;

    while (t.tabela[indice] != TabelaHashAberta::VAZIO) {
        if (t.tabela[indice] == chave) return true;

        indice = (indice + 1) % t.tabela.size();
        if (indice == indiceInicial) break; // percorreu toda a tabela
    }

    return false;
}
```

O mesmo cuidado deve ser aplicado também às remoções. Nesse caso, ao remover um elemento, não se pode simplesmente
tornar a posição anteriormente ocupada por ele vazia — isso comprometeria a lógica utilizada por uma eventual busca
de um elemento qualquer posterior a essa remoção, que poderia parar precocemente ao encontrar essa posição vazia sem
ter, de fato, percorrido toda a sequência de sondagem. Sendo assim, duas alternativas podem ser adotadas:

1. **Deslocamento dos dados para a posição desocupada.**

   O deslocamento dos dados para a posição desocupada exige a verificação de, enquanto não se retorna à posição
   inicial ou não se chega a uma posição vazia, se o elemento não deve ser reposicionado. Caso determinado elemento
   se encontre numa posição correspondente ao cálculo da sua própria função hash, então ele não deve ser
   reposicionado.

   Veja o pseudocódigo para uma possível implementação de tabela hash com endereçamento aberto e remoção por meio do
   deslocamento dos elementos:

   ```
   function remove(key)
       i := find_slot(key)
       if slot[i] is unoccupied
           return   // key is not in the table
       j := i
       loop
           j := (j+1) mod num_slots
           if slot[j] is unoccupied
               exit loop
           k := hash(slot[j].key) mod num_slots
           if (j > i and (k <= i or k > j)) or
              (j < i and (k <= i and k > j))
               slot[i] := slot[j]
               i := j
       mark slot[i] as unoccupied
   ```

2. **Marcar a posição livre como disponível para uso**, utilizando um valor simbólico, como -1, para tal. Assim,
   podemos diferenciar uma posição que sempre esteve livre de uma que se tornou livre após a remoção de um elemento
   que a ocupava — essa marca costuma ser chamada de **lápide** (*tombstone*), pois sinaliza que "algo esteve aqui",
   permitindo que a busca continue sua sondagem através dela sem interromper prematuramente, ao mesmo tempo em que
   permite que novas inserções reocupem essa posição.

   Após muitas remoções, essa estratégia começa a comprometer a eficiência da busca, sendo necessário, eventualmente,
   realizar a reinserção (rehash) de todos os elementos atuais numa nova tabela.

## Vantagens e Desvantagens

### Colisão por Encadeamento

- Suporta um fator de carga maior que 1 sem degradar drasticamente, já que múltiplos elementos podem coexistir na
  mesma posição;
- A remoção de um elemento é simples, bastando retirá-lo da lista correspondente, sem afetar as demais posições da
  tabela;
- Exige memória adicional para os ponteiros/estrutura das listas em cada posição;
- No pior caso — todas as chaves mapeadas para a mesma posição —, a busca degenera para $O(n)$, equivalente a uma
  busca linear numa lista.

### Colisão por Endereçamento Aberto

- Não exige memória adicional para ponteiros, já que todos os elementos residem diretamente no array da tabela,
  tornando-o mais eficiente em termos de uso de cache/memória;
- É obrigatório manter o fator de carga abaixo de 1 (geralmente, bem abaixo de 75%), já que a tabela não pode conter
  mais elementos do que posições;
- A remoção é mais complexa, exigindo deslocamento de elementos ou o uso de marcações de posições removidas
  (lápides);
- Sofre com o fenômeno de **agrupamento primário** (*clustering*), no qual sequências de posições ocupadas tendem a
  crescer, aumentando o tempo médio das buscas subsequentes.
