cmake_minimum_required(VERSION 3.16)
project(Bot C)

set(CMAKE_C_STANDARD 99)

add_executable(Bot main.c estrategia.c estrategia.h Dados.c Dados.h Interface.c Interface.h Logicadoprograma.c Logicadoprograma.h Listas.c Listas.h)