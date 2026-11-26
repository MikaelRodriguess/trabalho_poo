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

add_executable(demo src/main.cpp)
target_compile_options(demo PRIVATE ${PORTAO_DE_AVISOS})
