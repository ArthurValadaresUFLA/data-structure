/*
# Arquivos - Fibonacci Pares


Faça um programa que receba do usuário um número N e escreva em arquivo todos os
números pares que fazem parte da sequência de Fibonacci, mas que sejam menores
ou iguais aseu N-ésimo termo. O nome do arquivo de saída deve ser recebido do
usuário.

Considere que a sequência de Fibonacci é definida como:

* F(0) = 0;
* F(1) = 1;
* F(n) = F(n-1) + F(n-2) , n > 2;

**Obs.:** Considere que o zero é o primeiro termo da sequência, assim, se
usuário digitar N, o programa deve gerar N-1 valores da sequência.

**Obs.:** Lembre-se que " 0 2 8 34 " é diferente de " 02834 ".

### Entradas

```
1. Nome do arquivo de texto a ser criado;
2. Número N de termos da sequência a serem gerados.
```

### Saídas

```
1. Elemento(s) par(es) do conjunto N da sequência, escrito(s) no arquivo criado.
```

### Exemplo de Entrada

```
fib-pares.txt
10
```

### Arquivo de Saída (fib-pares.txt)

```
0 2 8 34
```

### Exemplo de Entrada

```
ricci.txt
40
```

### Arquivo de Saída (ricci.txt)

```
0 2 8 34 144 610 2584 10946 46368 196418 832040 3524578 14930352 63245986
```
*/

#include <fstream>
#include <iostream>

int calculaFib(int n) {

  if (n <= 1)
    return n;
  return calculaFib(n - 1) + calculaFib(n - 2);
}

int main() {

  std::string nomeArq;
  int n, fib;
  std::cin >> nomeArq >> n;

  std::ofstream arq(nomeArq);

  for (int i{0}; i < n; i++) {
    fib = calculaFib(i);
    if (!(fib % 2))
      arq << fib << " ";
  }

  return 0;
}
