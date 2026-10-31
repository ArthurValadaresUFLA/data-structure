/*
# Fila circular em vetor


Filas podem ser implementadas com armazenamento de dados em vetor, se a
capacidade fixa não for um problema. Nesse caso, é importante controlar os
índices para "dar a volta" no vetor sempre que for necessário. Uma fila assim
pode ser chamada de fila circular.

Faça a implementação de uma fila circular fazendo com que a inserção (método
Enfileirar) sempre use o início do vetor (posição zero) quando a fila estiver
vazia.

### Entradas

```
Inicialmente, o programa lê um número inteiro que é capacidade da fila a ser
criada.

Depois, o programa lê códigos de comandos a executar. Sempre um caractere
identificando o comando seguido dos parâmetros necessários para executar o
comando, se houverem. Os códigos de comandos são:

    . t - para terminar a execução do programa
    . e - para enfileirar um valor - seguido do valor (número inteiro)
    . d - para desenfileirar um valor
    . i - para escrever as informações da fila (atributos e conteúdo)
```

### Saídas

```
Os comandos d e i são os únicos que produzem saída de dados. Cada um pode ser
observado no exemplo.
```

### Exemplo de Entrada e Saída juntos

```
3
e 1
e 2
e 3
i
tamanho=3 capacidade=3 inicio=0 fim=2
1 2 3
d
1
e 4
i
tamanho=3 capacidade=3 inicio=1 fim=0
2 3 4
d
2
d
3
i
tamanho=1 capacidade=3 inicio=0 fim=0
4
t
```
*/

#include <iostream>
#include <stdexcept>

typedef int Dado;
const int INDEX_NULO{-1};

class FilaArr {
private:
  int indexInicio, indexFim;
  unsigned int tamanho;
  const unsigned int capacidade;
  Dado *dadoArr;

public:
  FilaArr(int capacidade = 10);
  ~FilaArr();
  void enfileira(const Dado &d);
  Dado desenfileira();
  Dado espiarInicio();
  void limparTudo();
  unsigned int getTamanho();
  bool vazia();
  bool cheia();
  void info();
};

FilaArr::FilaArr(int capacidade) : capacidade(capacidade) {
  indexInicio = indexFim = INDEX_NULO;
  dadoArr = new Dado[capacidade];
  tamanho = 0;
}

FilaArr::~FilaArr() { delete[] dadoArr; }

void FilaArr::enfileira(const Dado &d) {

  if (cheia())
    throw std::runtime_error("Erro: queue cheia!");

  if (vazia())
    indexInicio = 0;
  indexFim = (indexFim + 1) % capacidade;

  dadoArr[indexFim] = d;

  tamanho++;
}

Dado FilaArr::desenfileira() {
  if (vazia())
    throw std::runtime_error("Erro: queue vazia!");

  Dado temp = dadoArr[indexInicio];
  tamanho--;

  if (vazia())
    indexInicio = indexFim = INDEX_NULO;
  else
    indexInicio = (indexInicio + 1) % capacidade;

  return temp;
}

Dado FilaArr::espiarInicio() {
  if (vazia())
    throw std::runtime_error("Erro: queue vazia!");

  return dadoArr[indexInicio];
}

void FilaArr::limparTudo() {
  indexInicio = indexFim = INDEX_NULO;
  tamanho = 0;
}

unsigned int FilaArr::getTamanho() { return tamanho; }

bool FilaArr::vazia() { return !bool(tamanho); }

bool FilaArr::cheia() { return (tamanho == capacidade); }

void FilaArr::info() {

  std::cout << "tamanho=" << tamanho << " capacidade=" << capacidade
            << " inicio=" << indexInicio << " fim=" << indexFim << "\n";

  for (int i{0}; i < tamanho; i++)
    std::cout << dadoArr[(indexInicio + i) % capacidade] << " ";

  std::cout << "\n";
}

int main() {

  Dado d;
  char opcao;

  int n;
  std::cin >> n;

  FilaArr fila(n);

  do {

    try {

      std::cin >> opcao;

      switch (opcao) {
      case 'e': // enfileirar elemento
        std::cin >> d;
        fila.enfileira(d);
        break;
      case 'd': // desenfileirar elemento
        d = fila.desenfileira();
        std::cout << d << "\n";
        break;
      case 'i':
        fila.info();
        break;
      case 't':
        break;
      default:
        std::cout << "opcao invalida\n";
      }

    } catch (std::runtime_error &err) {
      std::cout << err.what() << "\n";
    }

  } while (opcao != 't');

  return 0;
}
