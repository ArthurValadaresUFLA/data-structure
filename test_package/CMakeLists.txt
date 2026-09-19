cmake_minimum_required(VERSION 3.23)

project(data-structure-tests CXX)

# O data-structure-config.cmake e o Catch2Config.cmake são gerados pelo
# CMakeDeps do Conan a partir de requirements()/build_requirements() do
# conanfile.py deste diretório (test_package).
find_package(data-structure CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

# A suíte de testes unitários da biblioteca vive aqui, não no projeto
# principal: assim, quem consome o data-structure via add_subdirectory() não
# precisa do Catch2, e `conan create` valida empacotamento e comportamento
# em uma única etapa.
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)

add_executable(unit_tests ${TEST_SOURCES})

# O alvo importado é header-only: traz o include path (agora namespaced em
# data-structure/) e o padrão C++17, sem nenhuma biblioteca para linkar.
target_link_libraries(unit_tests PRIVATE
        data-structure::data-structure
        Catch2::Catch2WithMain)

enable_testing()
add_test(NAME unit_tests COMMAND unit_tests)

