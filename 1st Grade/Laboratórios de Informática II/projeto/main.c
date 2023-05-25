/**
@file main.c
Ficheiro main do projeto.
*/
#include <stdio.h>
#include "Dados.h"
#include "Interface.h"
#include "Logicadoprograma.h"

/**==================================OOOOOOO  JOGO DE MESA: "RASTROS"==================================================*/

/** @brief Função principal.*/
int main() {
    ESTADO *e = inicializar_estado();
    int ciclo;

    printf("\t\t\tRASTROS\n"
           "Comandos do jogo:\n\n"
           "Efetuar uma jogada:                     -> coluna[a-h] e linha [1-8]\n"
           "Ver os movimentos:                      -> 'movs'\n"
           "Ver o tabuleiro:                        -> 'tab'\n"
           "Save o progresso:                       -> 'gr Estado.txt'\n"
           "Load o progresso:                       -> 'ler Estado.txt'\n"
           "Ver o Estado de uma jogada passada:     -> 'pos x', onde x é p nº da jogada\n"
           "Continuar a partir dessa jogada:        -> só efetua uma jogada válida\n"
           "Efetuar uma jogada aleatória:           -> 'jog'\n"
           "Efetuar uma jogada mais 'melhor':       -> 'jog2'\n"
           "Sair do jogo:                           -> 'Q'\n"
           "\n"
           "Bom jogo ;)\n\n\n");

    do{

        ciclo = interpretador(e);
        atualiza_num_comandos(e);
        if (end_game(e)!=0)
        {
            printf("//===========================//\n"
                          "Game over! Parabéns jogador: %d\n"
                          "//==========================//\n", end_game(e));
            ciclo = 0;
        }

    }while (ciclo != 0);

    return 0;
}

/**===================================================================================================================*/
