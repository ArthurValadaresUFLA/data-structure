/*
# Arquivo Tipado - Cadastro de alunos


Uma escola resolveu criar um sistema para fazer o registro de notas dos seus
alunos. Para isso, você deve criar um programa que recebe as seguintes
informações: número total de alunos e para cada aluno o nome, número de
matrícula e nota final do mesmo. É garantido que os dados serão fornecidos em
ordem crescente de matrícula. Esses dados devem ser gravados em um arquivo
tipado chamado de "alunos.bin".

A seguir, o programa recebe dois números de matrícula. O seu programa deve:
buscar o aluno no arquivo tipado com o primeiro número de matrícula (busca
binária). Em seguida, alterar esse campo para o segundo número de matrícula
fornecido. Esse registro agora deve ser reposicionado para manter a ordem do
arquivo tipado. Para isso, deve-se deslocar as posições dos registros no
arquivo. No final, um relatório contendo o nome e nota de cada aluno, na mesma
ordem que aparecem no arquivo tipado deve ser gerado na tela.

**OBS:** Não é permitida a utilização de vetores ou matrizes nesse programa.

### Entradas

```
1. Número de Alunos - (inteiro)
2. Sequência de dados de aluno: nome (sem espaco), matrícula, nota - (string,
inteiro, real)
3. matrícula do registro que deve ser modificado
4. nova matrícula
```

### Saídas

```
1. Lista de alunos ordenada (nome, nota)
```

### Exemplo de Entrada

```
3
Joao 1010 80.0
Paulo 1020 85.0
Ana 1030 90.5
1030 1000
```

### Exemplo de Saída

```
Ana 90.5
Joao 80.0
Paulo 85.0
```
*/

// ============================================================================
// alunos_binario.cpp
//
// Reescrita orientada a objetos do programa original de manipulação de um
// arquivo binário de alunos.
//
// RESTRIÇÃO DESTA VERSÃO: nenhum vetor/matriz/coleção de Aluno em memória.
// Isso significa que TODA a lógica — busca binária e reordenação — precisa
// operar diretamente sobre posições do arquivo, carregando **um único
// registro por vez** (exatamente como o programa original fazia, só que
// organizado em classes). Por isso não há mais std::vector<Aluno>: em vez
// de ler tudo para a memória, cada operação faz seekg/seekp + read/write de
// um Aluno isolado, usa o que precisa, e "esquece" o registro antes de ir
// para o próximo.
//
// (O único array que sobra é o char[100] DENTRO da classe Aluno, para o
// campo nome — isso não é uma coleção de alunos, é só o espaço fixo de UM
// campo de UM registro, indispensável para um arquivo de registros de
// tamanho fixo. É diferente do que a restrição proíbe: nenhuma estrutura
// guarda mais de um Aluno na memória ao mesmo tempo.)
//
// Padrões e técnicas usados:
//   • Aluno              -> entidade de domínio (o "registro").
//   • RepositorioAlunos  -> Design Pattern REPOSITORY: concentra todo o
//                           conhecimento de "como" persistir (fstream,
//                           seekg/seekp, sizeof, ios::binary...). O resto do
//                           programa só chama métodos de alto nível, sem
//                           saber que existe um arquivo por trás.
//   • criarApartirDeEntrada -> FACTORY METHOD: centraliza a criação de um
//                           Aluno a partir da entrada padrão.
//   • reposicionarAluno  -> técnica de "insertion move": o mesmo princípio
//                           de uma inserção do Insertion Sort, só que sobre
//                           um arquivo em disco, deslocando um vizinho por
//                           vez até achar a posição correta.
//   • std::fstream como variável local -> RAII: fecha sozinho ao sair de
//                           escopo, sem precisar chamar close() manualmente.
// ============================================================================

#include <algorithm> // std::copy_n, std::min
#include <fstream>   // std::ifstream / std::ofstream / std::fstream
#include <iostream>
#include <optional>  // std::optional (para "encontrei ou não encontrei")
#include <stdexcept> // std::runtime_error
#include <string>
#include <type_traits> // std::is_trivially_copyable

// ============================================================================
// ENTIDADE: Aluno
//
// Continua sendo, na essência, um registro de tamanho fixo — isso é
// PROPOSITAL: é exatamente esse tamanho fixo (sizeof(Aluno) sempre igual)
// que permite calcular a posição de qualquer registro no arquivo apenas
// multiplicando o índice por sizeof(Aluno), sem precisar de separadores.
// ============================================================================
class Aluno {
public:
  static constexpr std::size_t TAMANHO_NOME = 100;

  Aluno() : nome_{}, matricula_(0), nota_(0.0f) {}

  // Factory Method: sabe como montar um Aluno a partir de um std::istream
  // (teclado, arquivo texto, stringstream...). Mantém a regra de criação
  // num único lugar.
  static Aluno criarApartirDeEntrada(std::istream &entrada) {
    Aluno aluno;
    std::string nomeTemporario;
    entrada >> nomeTemporario >> aluno.matricula_ >> aluno.nota_;
    aluno.setNome(nomeTemporario);
    return aluno;
  }

  void setNome(const std::string &nome) {
    std::fill(std::begin(nome_), std::end(nome_), '\0');
    const std::size_t quantidade = std::min(nome.size(), TAMANHO_NOME - 1);
    std::copy_n(nome.begin(), quantidade, nome_);
  }

  std::string getNome() const {
    // nome_ é garantidamente terminado em '\0' por causa do fill() acima,
    // então o construtor de std::string para na hora certa.
    return std::string(nome_);
  }

  int getMatricula() const { return matricula_; }
  void setMatricula(int matricula) { matricula_ = matricula; }

  float getNota() const { return nota_; }

  // Overload de operator<<: permite usar std::ostream_iterator para
  // imprimir uma lista inteira de alunos com um único std::copy (lá no main).
  friend std::ostream &operator<<(std::ostream &saida, const Aluno &aluno) {
    return saida << aluno.getNome() << ' ' << aluno.nota_;
  }

private:
  // Campo de tamanho fixo de UM único registro (não é uma coleção de
  // alunos). É o que torna cada registro sempre igual a sizeof(Aluno)
  // bytes, permitindo calcular a posição de qualquer aluno no arquivo
  // apenas com "indice * sizeof(Aluno)".
  char nome_[TAMANHO_NOME];
  int matricula_;
  float nota_;
};

// ESSENCIAL para gravação binária: Aluno precisa poder ter seus bytes crus
// copiados diretamente (via reinterpret_cast<char*>) para o disco e de volta.
// Isso só é seguro se a classe for "trivially copyable" (sem ponteiros
// internos, sem construtor de cópia customizado, sem virtual...). O
// static_assert abaixo faz o COMPILADOR barrar qualquer alteração futura
// que quebre essa premissa, em vez de o bug aparecer só em tempo de execução.
static_assert(std::is_trivially_copyable<Aluno>::value,
              "Aluno precisa ser trivially copyable para leitura/escrita "
              "binaria direta.");

// ============================================================================
// REPOSITORY: RepositorioAlunos
//
// Isola completamente a mecânica de arquivo binário. NENHUM método aqui
// mantém mais de um Aluno na memória ao mesmo tempo: cada leitura devolve
// um único registro, usado e descartado antes do próximo seekg/seekp.
// ============================================================================
class RepositorioAlunos {
public:
  explicit RepositorioAlunos(std::string caminhoArquivo)
      : caminho_(std::move(caminhoArquivo)) {}

  // Fase de carga inicial: cria o arquivo do zero e grava um aluno de
  // cada vez, lendo direto da entrada informada. Repare que "aluno" é
  // uma única variável reaproveitada a cada volta do laço — nunca existe
  // uma coleção com todos os alunos simultaneamente.
  void gravarDaEntrada(int quantidade, std::istream &entrada) const {
    std::ofstream arquivo(caminho_, std::ios::binary | std::ios::trunc);
    if (!arquivo.is_open()) {
      throw std::runtime_error("Nao foi possivel criar '" + caminho_ + "'.");
    }
    for (int i = 0; i < quantidade; ++i) {
      Aluno aluno = Aluno::criarApartirDeEntrada(entrada);
      arquivo.write(reinterpret_cast<const char *>(&aluno), sizeof(Aluno));
    }
  }

  // Abre o arquivo (já existente) em modo misto leitura+escrita. É isso
  // que permite, mais adiante, ler um registro e sobrescrever outro sem
  // precisar fechar e reabrir o arquivo trocando de modo — diferente do
  // código original, que reabria o arquivo várias vezes.
  std::fstream abrirParaAtualizacao() const {
    std::fstream arquivo(caminho_,
                         std::ios::binary | std::ios::in | std::ios::out);
    if (!arquivo.is_open()) {
      throw std::runtime_error("Nao foi possivel abrir '" + caminho_ +
                               "' para atualizacao.");
    }
    return arquivo;
  }

  // Lê exatamente UM registro, na posição "indice". A posição em bytes é
  // sempre indice * sizeof(Aluno), porque todo registro tem tamanho fixo.
  Aluno lerRegistro(std::fstream &arquivo, int indice) const {
    Aluno aluno;
    arquivo.seekg(static_cast<std::streamoff>(indice) * sizeof(Aluno));
    arquivo.read(reinterpret_cast<char *>(&aluno), sizeof(Aluno));
    return aluno;
  }

  // Escreve exatamente UM registro na posição "indice", sobrescrevendo o
  // que já estava lá.
  void escreverRegistro(std::fstream &arquivo, int indice,
                        const Aluno &aluno) const {
    arquivo.seekp(static_cast<std::streamoff>(indice) * sizeof(Aluno));
    arquivo.write(reinterpret_cast<const char *>(&aluno), sizeof(Aluno));
    arquivo.flush(); // garante que a escrita vá ao disco antes de uma leitura
                     // seguinte
  }

  // Busca binária clássica, mas operando direto sobre posições do
  // arquivo: a cada comparação, exatamente UM registro é carregado do
  // disco, comparado e descartado. PRÉ-REQUISITO (igual ao original): o
  // arquivo precisa estar ordenado por matrícula.
  std::optional<int> buscarPorMatricula(std::fstream &arquivo, int quantidade,
                                        int matricula) const {
    int inicio = 0;
    int fim = quantidade - 1;

    while (inicio <= fim) {
      const int meio = inicio + (fim - inicio) / 2;
      const Aluno atual =
          lerRegistro(arquivo, meio); // um único registro na memória

      if (atual.getMatricula() == matricula) {
        return meio;
      } else if (matricula < atual.getMatricula()) {
        fim = meio - 1;
      } else {
        inicio = meio + 1;
      }
    }
    return std::nullopt; // não encontrado
  }

  // Atualiza a matrícula do registro em "posicaoAntiga" e o REPOSICIONA
  // no arquivo para manter tudo ordenado — sem nunca guardar mais de um
  // registro por vez na memória (além do próprio registro que está
  // sendo movido, mantido em "alunoAlvo" durante toda a operação).
  //
  // A técnica é a mesma de uma inserção do Insertion Sort: em vez de ler
  // um bloco inteiro e regravá-lo (como fazia o código original), aqui
  // cada vizinho é lido, comparado e, se preciso, "empurrado" um de cada
  // vez para o lugar que o registro deslocado vai deixar livre.
  void reposicionarAluno(std::fstream &arquivo, int quantidade,
                         int posicaoAntiga, int matriculaNova) const {
    Aluno alunoAlvo = lerRegistro(arquivo, posicaoAntiga);
    alunoAlvo.setMatricula(matriculaNova);

    int posicao = posicaoAntiga;

    // A nova matrícula é maior: o registro precisa "andar" para a
    // direita, empurrando para a esquerda cada vizinho menor que ela.
    while (posicao + 1 < quantidade) {
      Aluno vizinhoDireita = lerRegistro(arquivo, posicao + 1);
      if (vizinhoDireita.getMatricula() >= matriculaNova) {
        break; // já achou a posição correta
      }
      escreverRegistro(arquivo, posicao, vizinhoDireita); // empurra 1 vizinho
      ++posicao;
    }

    // A nova matrícula é menor: o registro precisa "andar" para a
    // esquerda, empurrando para a direita cada vizinho maior que ela.
    // (Só um dos dois laços de fato desloca algo — o outro encerra
    // imediatamente na primeira comparação.)
    while (posicao > 0) {
      Aluno vizinhoEsquerda = lerRegistro(arquivo, posicao - 1);
      if (vizinhoEsquerda.getMatricula() <= matriculaNova) {
        break;
      }
      escreverRegistro(arquivo, posicao, vizinhoEsquerda); // empurra 1 vizinho
      --posicao;
    }

    escreverRegistro(arquivo, posicao, alunoAlvo);
  }

  // Imprime todos os registros lendo um de cada vez — nunca carrega o
  // arquivo inteiro na memória.
  void imprimirTodos(std::fstream &arquivo, int quantidade,
                     std::ostream &saida = std::cout) const {
    for (int i = 0; i < quantidade; ++i) {
      const Aluno aluno = lerRegistro(arquivo, i); // um único registro por vez
      saida << aluno << '\n';
    }
  }

private:
  std::string caminho_;
};

// ============================================================================
// main(): orquestra os passos, sem nenhuma coleção de Aluno em memória —
// grava (um a um) -> busca binária no arquivo -> reposiciona no arquivo ->
// imprime (um a um), lendo sempre diretamente do disco.
// ============================================================================
int main() {
  try {
    int quantidadeAlunos;
    std::cin >> quantidadeAlunos;

    RepositorioAlunos repositorio("alunos.bin");
    repositorio.gravarDaEntrada(quantidadeAlunos, std::cin);
    // ATENÇÃO: a busca binária só funciona se esses alunos
    // forem informados em ordem crescente de matrícula.

    int matriculaBusca, novaMatricula;
    std::cin >> matriculaBusca >> novaMatricula;

    // Um único fstream, aberto em leitura+escrita, usado para tudo daqui
    // em diante — sem fechar/reabrir o arquivo entre etapas.
    std::fstream arquivo = repositorio.abrirParaAtualizacao();

    std::optional<int> posicaoEncontrada = repositorio.buscarPorMatricula(
        arquivo, quantidadeAlunos, matriculaBusca);

    if (posicaoEncontrada) {
      repositorio.reposicionarAluno(arquivo, quantidadeAlunos,
                                    *posicaoEncontrada, novaMatricula);
    }
    // Se não encontrado, simplesmente não há o que reposicionar — o
    // arquivo é impresso como está.

    repositorio.imprimirTodos(arquivo, quantidadeAlunos);

  } catch (const std::exception &erro) {
    std::cerr << "Erro: " << erro.what() << '\n';
    return 1;
  }

  return 0;
}
