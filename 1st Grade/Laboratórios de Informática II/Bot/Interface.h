/**
@file Interface.h
Definição do estado e das funções que o manipulam
*/
#ifndef LI2PL7G05_INTERFACE_H
#define LI2PL7G05_INTERFACE_H
#include "Dados.h"
#include <stdio.h>

/**=============================================CAMADA DA INTERFACE===================================================*/

                           /**----Funções relativas a impressão do tabuleiro----*/

/**
\brief Função que imprime uma casa do tabuleiro.
@param fp Apontador para um FILE
@param e Apontador para o ESTADO
@param i Número inteiro que corresponde ao número da linha
@param j Número inteiro que corresponde ao número da coluna
*/
void imprime_casa(FILE *fp, ESTADO *e, int i, int j);
/**
\brief Função que imprime o tabuleiro e o prompt.
@param fp Apontador para um FILE
@param e Apontador para o ESTADO
*/
void mostrar_tabuleiro(FILE *fp, ESTADO *e);

                       /**----Funções print que servem para imprimir ERROS e os Movimentos----*/

/**
\brief Função que imprime os erros para o jogador.
@param erro variável do tipo ERROS
*/
int print_erro(ERROS erro);

/**
\brief Função que imprime o movimento do jogador 1.
@param fp Apontador para um FILE
@param e Apontador para o ESTADO
@param c a COORDENADA
@param num inteiro para o número da jogada
*/
void print_mov(FILE *fp, COORDENADA c, int jogada);

/**
\brief Função que recebe um ESTADO e um nº que corresponde ao nº de jogadas e imprime essa linha.
@param fp Apontador para um FILE
@param e Apontador para o ESTADO
@param num inteiro para o número da jogada
*/
void print_jogadas_completas(ESTADO *e, FILE *fp, int jogada);

                           /**----Função principal responsável pelo comando 'movs'----*/

/**
\brief Função que imprime os movimentos num File, usada para imprimir os movs logo a seguir ao tabuleiro.
@param e Apontador para o ESTADO
*/
int movimentos(ESTADO *e, FILE *fp);

                             /**----Função principal responsável pelo comando 'gr'----*/

/**
\brief Função que grava o Estado do jogo num ficheiro.
@param e Apontador para o ESTADO
@param c string que contém o nome do file
*/
int gravar(ESTADO *e, char c[]);

                                /**----Função principal responsável pelo comando 'ler'----*/

/**
\brief Função que lê os dados de um ficheiro e modifica o Estado.
@param e Apontador para o ESTADO
@param c string que contém o nome do file
*/
int ler(ESTADO *e, char c[]);

                             /**----Funções principais responsáveis pelo comando 'pos'----*/

/**
\brief Função que mostra o Estado anterior sem alterar o atual.
@param e Apontador para o ESTADO
@param num inteiro para o número da jogada
*/
void pos_nao_atualiza(ESTADO *e, int n_jogada);

/**
\brief Função que altera o Estado atual por um anterior.
@param e Apontador para o ESTADO
@param num inteiro para o número da jogada
*/
void pos_atualiza(ESTADO *e, int n_jogada);

                      /**----Funções principais responsáveis pelos comandos 'jog' e 'jog2'----*/

/**
\brief Função que joga automaticamente de acordo com a Herística Euclidiana.
@param e Apontador para o ESTADO
*/
int jogada_automatica(ESTADO *e);

/**
\brief Função que gera uma jogada automática mas aleatória.
@param e Apontador para o ESTADO
*/
COORDENADA jog(ESTADO *e);

                            /**----Função responsável por imprimir o prompt do jogo----*/

/**
\brief Função que corresponde ao prompt do jogo.
@param e Apontador para o ESTADO
*/
void prompt(ESTADO*e);

                   /**----Funções responsáveis por interpertar as jogadas e os comandos do jogo----*/

/**
\brief Função que interpreta só os comandos do joga.
@param e Apontador para o ESTADO
@param string para linha
*/
int comandos(ESTADO *e, char *linha);

/**
\brief Função que representa o interpretador do jogo.
@param e Apontador para o ESTADO
*/
int interpretador(ESTADO *e);



#endif //LI2PL7G05_INTERFACE_H
