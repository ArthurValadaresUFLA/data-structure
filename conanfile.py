from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout


class DataStructureRecipe(ConanFile):
    name = "data-structure"
    version = "0.1.0"

    # Todas as estruturas de dados são templates definidos em cabeçalhos, logo o
    # pacote não contém binário algum.
    package_type = "header-library"

    # Metadados
    # TODO: definir a licença do projeto (não há arquivo LICENSE no repositório).
    author = "Arthur Valadares Campideli, Gabriel Coelho"
    url = "https://github.com/ArthurValadaresUFLA/data-structure"
    description = (
        "Estruturas de dados genéricas (pilhas, filas, listas, heaps, tabelas "
        "hash e árvores) implementadas como TADs na disciplina GAC108 - DCC/UFLA."
    )
    topics = ("data-structures", "algorithms", "header-only", "cpp17", "educational")

    # Settings são declarados apenas para que o CMakeToolchain gere a
    # configuração corretamente (padrão C++, etc.), mesmo sem produzir nenhum
    # binário: o package_id() abaixo limpa todos os settings do pacote. A
    # suíte de testes unitários (Catch2) não é compilada por esta receita --
    # ela vive em test_package e roda automaticamente após o `conan create`.
    settings = "os", "compiler", "build_type", "arch"

    # src/ precisa ser exportado junto com include/: os cabeçalhos incluem, ao
    # final, as definições de template que vivem lá.
    exports_sources = "CMakeLists.txt", "include/*", "src/*"

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_id(self):
        # Header-only: o conteúdo do pacote é idêntico para qualquer
        # compilador, arquitetura ou build_type.
        self.info.clear()

    def package_info(self):
        # Não há biblioteca para linkar; o consumidor recebe apenas o include
        # path. As definições de template em <package>/src são alcançadas por
        # caminho relativo a partir dos cabeçalhos, sem entrar no include path.
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []

