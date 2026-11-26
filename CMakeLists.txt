cmake_minimum_required(VERSION 3.16)
project(biblioteca LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# O portão de avisos da Unidade I. Qualquer aviso vira erro.
set(PORTAO_DE_AVISOS
    -Wall -Wextra -Wpedantic -Wshadow -Wold-style-cast -Wcast-align
    -Wconversion -Wsign-conversion -Wnon-virtual-dtor -Wdouble-promotion
    -Wformat=2 -Werror)

# As classes do domínio: uma biblioteca que não conhece std::cout.
add_library(biblioteca_core
    src/item_acervo.cpp
    src/livro.cpp
    src/revista.cpp
    src/dvd.cpp
    src/acervo.cpp)
target_include_directories(biblioteca_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(biblioteca_core PRIVATE ${PORTAO_DE_AVISOS})

# O programa de demonstração, que é quem imprime.
add_executable(demo src/main.cpp)
target_link_libraries(demo PRIVATE biblioteca_core)
target_compile_options(demo PRIVATE ${PORTAO_DE_AVISOS})
