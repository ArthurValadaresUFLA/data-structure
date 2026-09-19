# TAD's

Os **tipos abstratos de dados**, TAD's, são uma maneira de definir um novo tipo de dado, além daqueles disponibilizados
de forma primitiva pela linguagem de programação. Assim, com a definição dos **dados**, são definidas também
as **operações** que manipulam esse novo tipo de dado.

## Programação Orientada a Objetos (POO)

Porgramação orientada a objetos é um **paradigma de programação** no qual se faz a junção das variáveis às funções - que
ganham o nome de métodos - a fim de descrever entidades; os seus atributos unidos aos seus
comportamentos.

### Diferenciando métodos e atributos

No processo de abstração de um objeto, é de suma importância diferenciar o que constitui um comportamento, ação, método,
e o que constitui um atributo. A fim de auxiliar no processo de melhor entendimento e distinção pode-se estabelecer o
seguinte:

- Método: **Associado a verbo**, ao pensar naquilo que visa ser representado, tudo que é relativo a um verbo - assuma: '
  fazer' -
  pode ser entendido como um método. **Atenção:** Tente reduzir as sentenças ao verbo _faz_ e a um objeto direto /
  indireto.
- Atributo: **Associado a _objetos_ na sintaxe gramatical**, muitas pessoas não estão familiarizadas com a ordem
  canônica do Português, a fim de simplificar, tudo o que sucede quaisquer conjugação do verbo '_ser_' pode ser
  entendido como atributo.

#### Examplo

| Método                     | Atributo             |
|----------------------------|----------------------|
| Você **faz** a comida      | Você **é** pardo     |
| Você **faz** as atividades | Você **é** dedicado  |
| Você **faz** os trabalhos  | Você **é** estudioso |

### Pilares do OOP

Nesse sentido, vale ressaltar os quatro **pilares** que determinam o desenvolvimento orientado a objetos:

- [**Abstração**](#abstração);
- [**Encapsulamento**](#encapsulamento);
- [**Herança**](#herança);
- [**Polimorfismo**](#polimorfismo);

#### Abstração

Consiste no processo de retratar, de forma programática, os atributos e comportamentos relevantes à
problemática, isto é, no que tange, por exemplo, ao sistema integrado de um hospital, no contexto de uma enfermeira,
pouco importa as habilidades culinárias, em contrapartida, as capacidades de ressucitação e as certificações são
relevantes para o sistema.

#### Encapsulamento

Se baseia na ideia de esconder o real funcionamento interno do objeto, expondo somente métodos e atributos necessários
ao funcionamento por parte de outrem. Por exemplo - se não conheces, farás uso disso descorrer do curso - quando se
usa bibliotecas de terceiros, o funcionamento interno dela não precisa ser exposto, há diversos arquivos,
atributos e métodos internos que não podem ou não devem ser acessados, os responsáveis por escrever a biblioteca vão
expor aos utilizadores poucos arquivos e funcionalidades do que de fato contitui a biblioteca, você só terá acesso
àquilo
que faz sentido, na visão dos contribuidores, posto os objetivos da biblioteca. Em outras palavras, até onde isso não
lhe afeta, você não precisa, não deve ou necessita se importa como a biblioteca funciona internamente, basta que
funcione.

A exemplo da biblioteca `<queue>` em C++, ela tem uma classe que faz a abstração de uma fila, você sabendo como uma fila
funciona, não importa como ela vai alocar, desalocar ou gerir a memória usada, se vai estar na heap, se vai estar na
stack, se vai usar encadeamento ou arranjo, são muitas as possibilidas, mas todas contituem filas, e você só
precisa de uma fila. Se você ler a documentação da respetiva biblioteca vai ser os métodos que necessita para fazer uso
devido dela.

#### Herança

Você lembra das aulas de cladística no ensino médio? Não, né? Pois é, mas lembra do Darwin, né? "Os ser humanos vieram
do macaco", algo assim, a frase está errada, mas vai servir de base. A frase certa seria algo como: "O homossapien
possui um ancestral em comum com o pan troglodytes". Ok. Agora....o que Biologia tem a ver com computação?!
Existem várias terminologias no processo de entendimento da cladística, mas, para nós, no contexto da computação, só
importa entender que as classes B e C possuem um _ancestral_ comum. O que seria esse ancestral comum então?
Uma… classe.

Ainda no exemplo da cladística, o ser humano - Homo sapiens sapiens - e o chimpanzé - pan troglodytes -, pertencem ambos
à ordem dos primatas. De forma simplória, vejamos as características dos primatas:

- Cérebro grande;
- Olhos voltados para frente;
- Polegares opositores;

Você pode não ser um biólogo - ou quem sabe é, não sei dizer -, mas pelo pouco conhecimento que a cultura provê sobre o
assunto, você pode saber - ou não -, que os chimpanzés possuem essas caracteríticas, se olhares no espeho - ou na câmera
do celular se preferir -, vais ver que você, um ser humano, também tem essas caracteríticas. Isso que dizer que a
_classe_ **ser humano**, denominada H, daqui pra frente, em algum momento na árvore de herança, herda de uma mesma
_classe_ que o **Chimpanzé**, chamemos de C. Isso significa que os atributos contidos em P, esse ancestral comum, também 
estão presentes em C e H.

Isso significa que C e H são iguais, certo? De jeito nenhum. Quando comparamos classes temos de deixar claro os escopos,
o contexto. C e H são classes diferentes, possuem conjuntos de atributos diferentes, mas, quando reduzidas a P, isto é,
ignorados todos os tributos que não estão em P, aí podemos dizer que elas são iguais, mas depende, novamente, do contexto.

Imagine dois colegas da sua sala, por exemplo, eles são iguais? Ora, se ambos são seres humanos, a resposta deve ser:
sim. Entretanto, não, é diferente compararmos instâncias e classes, para tal, vamos fazer a diferenciação.

##### Classes e Instâncias

Como supradito, uma classe pode ser entendida como a união dos atributos e métodos, ações, relativas a um objeto que são
relevantes ao contexto. Quando você tem uma classe, ela é uma ideia abstrata - não confuda com classe abstrata, se
necessário explico mais adiante -, quando você imagina um ser humano, você imagina todos os respectivos atributos,
você dá valores a eles, mas o que seriam esses valores? Bem... um ser humano tem cabelo, isso é um atributo, mas como o
cabelo é, crespo, cachiado, liso ou ondulado, são os valores desses atributos. Quando você dá valores aos atributos você
cria uma instância de classe.

**Os atributos de uma classe não têm valores, os de uma instância têm**.

#### Polimorfismo

Leia o conteúdo de [Herança](#herança), foque no exemplo de biologia. Vai ser útil aqui.
Todos os animais alimentam-se de alguma forma, isso inclui Chimpanzés e seres Humanos. Primatas também comem. Como eu
disse em [Diferenciando Métodos e Atributos](#diferenciando-métodos-e-atributos), comer, um verbo, no contexto de
programação orientada a objetos, pode ser entendido como um método. Pois: você come da mesma forma que um
chimpanzé? Eu quero crer que não... Enfim, você e um chimpanzé são ambos Primatas, mas, no processo evolutivo, vocês *sobrescreveram* os métodos heradados do ancestral comum, substituiram o herdado pela versão relativa à sua classe. É o
mesmo método, digamos...

```c++
// Esse é o herdado do ancestral comum
void comer();

//Esse é o seu
void comer() override {
    // Comer com talheres
}

//Esse é o do chimpanzé
void comer() override {
    //Comer... sem talheres
}

```

Polimorfismo é uma palavra originada do grego. É a junção de _poli-_, que significa muitos e _-morfo_, forma, isso
significa que, numa tradução literal, **polimosfismo** pode ser entendido como **muitas formas**.

**Polimosfismo é o processo de sobrescrever métodos herdados de modo a manter os argumentos e tipos de retorno, mas
mudando a lógica de funcionamento.**

## Construtores e Destrutores

### Construtores

```cpp
Animal::Animal(int id, string nome, int idade, string raca, float peso){

    this->id = id;
    this->nome = nome;
    this->idade = idade;
    this->raca = raca;
    this->peso = peso;

    consultas = new Consulta[5];

}
```

- São métodos especiais que, no C++, possuem o **mesmo nome da classe** sendo utilizados para **inicializar uma
  instância** da
  mesma.
- São **invocados uma única vez**, apenas no momento de inicialização da classe.
- Caso nenhum construtor seja definido, o compilador automaticamente define um construtor padrão, o qual não recebe
  nenhum parâmetro e também não faz nada. Dessa forma, impossibilitado que algum objeto seja instanciado sem nenhuma
  inicialização.
- Construtores permitem uma sintaxe alternativa para inicializar os atributos chamada **"inicialização em lista"**.
  Nesse caso, o corpo do construtor é executado após a inicialização dos atributos em lista. Atributos constantes ou
  referências devem, obrigatoriamente, ser inicializados em lista.

Vetores ou estruturas sem construtores só podem ser inicializados diretamente;

Segue o exemplo de uma inicialização em lista:

```cpp
Animal::Animal(int id, string nome, int idade, string raca, float peso) : 
    id(id), nome(nome), idade(idade), raca(raca), peso(peso), consultas(new Consulta[5]){
    
}
```

### Construtores de cópia

- Constrói um novo objeto a partir de um outro já existente, que pertence a mesma classe. Basicamente, se trata de um
  construtor que recebe como parâmetro um objeto da mesma classe, passado como referência (evitar recursão).
- Compilador fornece um construtor de cópia padrão, o qual simplesmente faz uma cópia de todos os atributos do objeto
  passado como parâmetro.
- Quando um objeto é passado como parâmetro de uma função por valor, o construtor de cópia é automaticamente invocado.

Vale ressaltar a necessidade de fazer a sobrecarga do construtor de cópia quando o objeto possui campos dinamicamente
alocados. Isso se deve a tais campos serem copiados e o novo objeto também passar a apontar para a mesma região de
memória anteriormente alocada. Nesse caso, alterações indevidas podem ocorrer nessas regiões de memória ou até mesmo a
desalocação dessas regiões
após o objeto copiado encerrar o seu ciclo de vida.

O mesmo vale para operações de atribuição, que também passa a exigir a sobrecarga do operador de atribuição.

### Destrutores

```cpp
Animal::~Animal(){

    delete[] consultas;
}
```

- São métodos especiais das classes sendo indicados pelo nome da classe precedido pelo caractere **"~"**.
- São invocados implicitamente quando um objeto é destruído.
- Compilador também fornece um destrutor padrão, caso nenhum seja definido explicitamente (não executa nenhuma
  instrução).
- Geralmente, os atributos da classe alocados dinâmicamente são desalocados nos destrutores, evitando uso indevido da
  memória.

## Sobrecarga de métodos

C++ permite a criação de métodos com mesmo nome, porém assinaturas diferentes. Por assinatura diferente, diz-se um
conjunto de parâmetros diferentes, que pode se tratar do número de parâmetros, do
tipo deles, ou até mesmo da ordem em que são definidos. Sobrecarga de métodos se estende, inclusive, para os métodos
especiais das classes, como construtores e destrutores. Durante a chamada do método sobrecarregado, o compilador
identifica aquele compatível com os parâmetros passados
e, então, o executa.

## Sobrecarga de operadores

- C++ também permite a sobrecarga de operadores, o que permite adicionar funcionalidades dependendo dos
  argumentos fornecidos.
- Nem todos os operadores podem ser sobrecarregados.
- Pelo menos um dos operandos deve ser um tipo de dado criado pelo usuário.

Sobrecarga pode ser feita de duas formas:

- Método da classe:

Veja a criação de dois métodos da classe que sobrecarregam os operadores de comparação '>' e '<', respectivamente.
Nesse caso, tais métodos retornam um booleano resultado da comparação da idade entre dois animais.

As assinaturas dos métodos são definidos no interior da classe:

```cpp
bool operator>(const Animal &a);
bool operator<(const Animal &a);
```

Veja a implementação dos métodos:

``` cpp
bool Animal::operator>(const Animal& a){
  return idade > a.idade;
}

bool Animal::operator<(const Animal& a){
  return idade < a.idade;
}
```

Veja como é feita a chamada dos métodos sobrecarregados:

```cpp
Animal animal_1 (1, "Bolinha", 7, "Cachorro", 42.5); // idade: 7
Animal animal_2 (2, "Miau", 10, "Gato", 32.8); // idade: 10

cout << (animal_1 > animal_2) << "\n"; // False
cout << (animal_1 < animal_2) << "\n"; // True
```

Implicitamente, tais métodos são invocados pelo objeto à esquerda do operador da seguinte forma:

```cpp
animal_1.operator>(animal_2);
animal_1.operator<(animal_2);
```

- Função externa "amiga" da classe:

  Se tratam de funções externas à classe, mas que foram definidas como "amigas" da mesma, permitindo, então, o
  acesso dessas funções aos seus atributos e métodos privados.

  Observe o exemplo no qual os operadores utilizados em conjunto com os objetos de stream são sobrecarregados.

  Nesse caso, seria impossível sobrecarregar tais operadores via algum método da classe, visto que o operando
  esquerdo não se trata de um objeto. Logo, ele não pode ser invocado pelo objeto em questão.

  As assinaturas são definidos no interior da classe:

```cpp
friend std::ostream & operator<<(std::ostream &output, const Animal& animal);
friend std::istream & operator>>(std::istream &input,Animal& animal);
```

Segue a implementação dessas funções:

```cpp
std::ostream & operator<<(std::ostream &output, const Animal& animal){

  output << "Nome: " << animal.nome << "\n";
  output << "Id: " << animal.id << "\n";
  return output;
}

std::istream & operator>>(std::istream &input, Animal& animal){

  input >> animal.nome >> animal.id;
  return input; 
}
```

Veja como é feita a chamada das funções:

```cpp
Animal animal_1, animal_2;

std::cin >> animal_1 >> animal_2;
std::cout << animal_1 << animal_2;
```

Note, também, que a referência aos objetos de stream 'cin' e 'cout' são retornadas ao final das operações,
permitindo o encadeamento de operações.

* Segue o exemplo da sobrecarga do operador de atribuição, nesse caso como um método da classe **Animal**:

```cpp
Animal& Animal::operator=(const Animal &a){
    
    id = a.id;
    nome = a.nome;
    idade = a.idade;
    raca = a.raca;
    peso = a.peso;

    // uma nova região de memória é alocada e a cópia dos dados é salva nessa região
    consultas = new Consulta[5];
    std::copy(a.consultas, a.consultas + 5, consultas);

    return *this;
}
```

Observe que uma referência do próprio objeto é retornada, permitindo o encadeamento de atribuições.

```cpp
animal_1 = animal_2 = animal_3;
```

## Extras

### Palavra-chave this

A palavra reservada **"this"** é usada para refenciar a própria instância quando algum de seus métodos é invocado. Ou
seja, basicamente, se trata de um ponteiro que aponta para a própria instância.

Passado como parâmetro, de forma implícita, em todos os métodos de uma classe (com exceção de métodos estáticos).

Geralmente, é utilizada em casos de ambiguidade entre os atributos da classe e os parâmetros da função.

### Métodos do tipo const

São métodos que possuem a palavra reservada **"const"** no final da sua assinatura.

Tais métodos não possuem capacidade de alterar o valor de qualquer atributo do objeto. Assim, os **atributos são
acessíveis apenas para leitura**.

Comumente utilizado em métodos **"getters**".

Segue o exemplo de um método do tipo **"const"**:

```cpp
int Animal::getIdade() const {

    // tal atribuição causaria um erro de compilação
    //idade = 10; 

    return idade;
}
```
