/*
# Ponteiros - Caça Palavras em Matriz


Desenvolva um programa que receba uma matriz nxn (n fornecido pelo usuário) de caracteres (um caractere em cada posição da matriz). O usuário digitará m palavras (m informado na entrada). O programa deve procurar a ocorrência de cada palavra na matriz, imprimindo as coordenadas da primeira letra ou -1 -1 se a palavra não existir. A procura deve ser feita na horizontal (da esquerda para direita) e na vertical (de cima para baixo).

**OBS:** Letras maiúsculas e minúsculas são diferenciadas. A matriz deve ser alocada dinamicamente. A função strlen() retorna o tamanho de uma string tipo C (vetor de caracteres) e o método length() ou size() pode ser usado para pegar o tamanho de uma string do C++.

### Entradas

```
1. Tamanho do lado da matriz (n)
2. Matriz de caracteres (nxn)
3. Número de palavras (m)
4. Palavras sem espaços, uma em cada linha
```

### Saídas

```
1. Posição da letra inicial de cada palavra na matriz, na ordem em que as palavras foram lidas.
```

### Exemplo de Entrada

```
3
A B C
D E F
G H I
2
BE
FI
```

### Exemplo de Saída

```
0 1
1 2
```
*/

#include <iostream>
#include <utility>

bool procuraHorizontal(char **matriz, int tamMatriz, const std::string &palavraBuscada, std::pair<int, int>  indexMatriz){

    int tamPalavra{palavraBuscada.length()};

    if(tamPalavra > (tamMatriz - indexMatriz.second))
        return false;
    
    int i{0};
    while(i < tamPalavra && matriz[indexMatriz.first][i + indexMatriz.second] == palavraBuscada[i])
        i++;
    
    return (i == tamPalavra);

}

bool procuraVertical(char **matriz, int tamMatriz, const std::string &palavraBuscada, std::pair<int, int>  indexMatriz){

    int tamPalavra{palavraBuscada.length()};

    if(tamPalavra > (tamMatriz - indexMatriz.first))
        return false;
    
    int i{0};
    while(i < tamPalavra && matriz[i + indexMatriz.first][indexMatriz.second] == palavraBuscada[i])
        i++;
    
    return (i == tamPalavra);

}

int main(){

    int n;
    std::cin >> n;

    char **matriz{new char*[n]};
    for(int i{0}; i<n; i++)
        matriz[i] = new char[n];
    

    for(int i{0}; i<n; i++)
        for(int j{0}; j<n; j++)
            std::cin >> matriz[i][j];
    
    int m;
    std::cin >> m;
    std::string palavra;

    int k;

    for(int i{0}; i<m; i++){
        std::cin >> palavra;

        k = 0;
        while(
            k < n*n && 
            !procuraHorizontal(matriz, n, palavra, std::make_pair(int(k/n), (k%n))) &&
            !procuraVertical(matriz, n, palavra, std::make_pair(int(k/n), (k%n)))
        ){
            k++;
        }

        if(k == n*n){
            std::cout << "-1 -1\n";
        }else{
            std::cout << int(k/n) << " " << (k%n) << "\n";
        }

    }

    for(int i{0}; i<n; i++)
        delete[] matriz[i];
    delete[] matriz;

    return 0;
}