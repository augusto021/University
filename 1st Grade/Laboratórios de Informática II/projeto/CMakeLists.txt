cmake_minimum_required(VERSION 3.15)
project(LI2PL7G05 C)

set(CMAKE_C_STANDARD 99)

add_executable(LI2PL7G05 main.c Dados.c Dados.h Interface.c Interface.h Logicadoprograma.c Logicadoprograma.h Listas.c Listas.h)


target_link_libraries(LI2PL7G05 m)
