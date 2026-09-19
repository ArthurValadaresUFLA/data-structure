from conan import ConanFile
from conan.tools.build import can_run
from conan.tools.cmake import CMake, cmake_layout


class DataStructureTestConan(ConanFile):
    """Suíte de testes unitários do data-structure.

    Vive em test_package por convenção do Conan -- roda automaticamente após o
    build() da receita principal, via `conan create` -- mas o que é compilado
    e executado aqui É a suíte de testes unitários da biblioteca (Catch2),
    não apenas um exemplo de consumo do pacote. Isso também valida, de
    quebra, que os cabeçalhos, as definições de template em src/ e o alvo
    data-structure::data-structure chegam íntegros ao consumidor.
    """

    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        # tested_reference_str é o pacote recém-criado pelo `conan create`.
        self.requires(self.tested_reference_str)

    def build_requirements(self):
        # Catch2 é necessário apenas para compilar a suíte de testes e não é
        # propagado para quem consome o data-structure.
        self.test_requires("catch2/3.7.0")

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        if can_run(self):
            cmake = CMake(self)
            cmake.test()

