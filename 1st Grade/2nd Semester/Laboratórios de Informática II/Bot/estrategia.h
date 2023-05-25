/**
@file estrategia.h
Definição das estratégias do bot.
*/
#ifndef BOT_ESTRATEGIA_H
#define BOT_ESTRATEGIA_H
#include "Dados.h"

/**
\brief Função que efetua a primeira jogada, se é o caso.
@param e Apontador para o ESTADO
@param plr inteiro para número do jogador
@param c A COORDENADA
*/
void first_play(ESTADO *e, int plr, COORDENADA c);

/**
\brief Funções que efetuam a segunda e terceira jogada se tudo correr como planeado.
@param e Apontador para o ESTADO
@param plr inteiro para número do jogador
@param c A COORDENADA
*/
void second_third(ESTADO *e, int plr, COORDENADA c);

/**
\brief Função que define as premissas da vitória.
@param e Apontador para o ESTADO
@param plr inteiro para número do jogador
@param c A COORDENADA
*/
int premissas_win(ESTADO *e, int plr, COORDENADA c);

/**
\brief Função que prende a branca, se for possível.
@param e Apontador para o ESTADO
@param c A COORDENADA
*/
int prende_branca(ESTADO *e, COORDENADA c);

/**
\brief Função auxiliar, da função jogar_pelas_bordas, mas apenas para o jogador1.
@param e Apontador para o ESTADO
@param branca A COORDENADA
*/
void jogada_para_player1(ESTADO *e,COORDENADA branc);

/**
\brief Função auxiliar, da função jogar_pelas_bordas, mas apenas para o jogador2.
@param e Apontador para o ESTADO
@param branca A COORDENADA
*/
void jogada_para_player2(ESTADO *e,COORDENADA branc);

/**
\brief Função que vai jogando pela borda do tabuleiro, na direção da nossa casa.
@param e Apontador para o ESTADO
@param plr inteiro para número do jogador
@param branca A COORDENADA
*/
void jogar_pelas_bordas( ESTADO *e, int plr, COORDENADA branc);

/**
\brief Função que retorna a Coordenada que seria a melhor jogada.
@param e Apontador para o ESTADO
@param plr inteiro para número do jogador
@param branca A COORDENADA
*/
void jogar_fino(ESTADO *e, int plr, COORDENADA branc);

/**
\brief Função que define a estratégia principal do jogo.
@param e Apontador para o ESTADO
@param plr inteiro para número do jogador
@param branca A COORDENADA
*/
void estrategia_main(ESTADO *e, int plr, COORDENADA branc);

#endif //BOT_ESTRATEGIA_H
