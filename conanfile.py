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

    # Opções repassadas ao CMake. Desligadas por padrão para que o pacote
    # criado não dependa de exemplos nem de Doxygen. Para compilar os exemplos:
    #   conan build . -o "&:build_examples=True"
    options = {
        "build_examples": [True, False],
        "build_docs": [True, False],
    }
    default_options = {
        "build_examples": False,
        "build_docs": False,
    }

    # src/ precisa ser exportado junto com include/: os cabeçalhos incluem, ao
    # final, as definições de template que vivem lá.
    # examples/ e doc/ são exportados porque o CMakeLists.txt os referencia
    # quando build_examples / build_docs estão ligados.
    exports_sources = (
        "CMakeLists.txt",
        "include/*",
        "src/*",
        "examples/*",
        "doc/*",
    )

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["DATA_STRUCTURE_BUILD_EXAMPLES"] = bool(
            self.options.build_examples
        )
        tc.variables["DATA_STRUCTURE_BUILD_DOCS"] = bool(self.options.build_docs)
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
        # compilador, arquitetura, build_type ou opção (clear() também
        # descarta build_examples e build_docs).
        self.info.clear()

    def package_info(self):
        # Não há biblioteca para linkar; o consumidor recebe apenas o include
        # path. As definições de template em <package>/src são alcançadas por
        # caminho relativo a partir dos cabeçalhos, sem entrar no include path.
        self.cpp_info.includedirs = ["include", "src"]
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
