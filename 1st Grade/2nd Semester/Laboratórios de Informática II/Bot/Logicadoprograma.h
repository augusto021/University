/**
@file Logicadoprograma.h
Definição das jogadas
*/
#ifndef LI2PL7G05_LOGICA_DO_PROGRAMA_H
#define LI2PL7G05_LOGICA_DO_PROGRAMA_H
#include "Dados.h"
#include "Listas.h"

/**
\brief Função que verifica se o nº inserido no comando "pos" é válido.
@param e Apontador para o Estado
@param num variável do tipo int
 */
int pos_valido(ESTADO *e, int num);

/**
\brief Função booleana que verifica se o último comando executado foi o pos.
@param e Apontador para Estado
*/
int comand_pos(ESTADO *e);

/**
\brief Função que atribui um número as posições a volta da peça branca:
* Posição superior esquerda  ==1
* Posição a cima             ==2
* Posição superior direita   ==3
* Posição a direita          ==4
* Posição inferior direita   ==5
* Posição a baixo            ==6
* Posição inferior esquerda  ==7
* Posição a esquerda         ==8
@param c A Coordenada
@param branca A Coordenada
*/
int posicao_em_relacao_branca(COORDENADA c, COORDENADA brc);

/**
\brief Função que verifica se uma jogada é completa.
@param play para coordenada JOGADA
*/
int jogada_completa(JOGADA play);

/**
\brief Função que converte uma COORDENADA para uma string.
@param c A Coordenada
*/
char* coord_to_str(COORDENADA coord);

/**
\brief Função que transforma uma string numa jogada.
@param str string que contém o nome do file
*/
COORDENADA str_to_coord(char str[]);

/**
\brief Função que verifica se uma casa está livre, isto é, se é vazia e pertence ao tabuleiro.
@param e Apontador para o Estado
@param c A Coordenada
*/
int casa_livre(ESTADO *e, COORDENADA c);

/**
\brief Função booleana que verifica se a distância da próxima jogada é válida.
@param e Apontador para o Estado
@param c A Coordenada
 */
int dist_valida(ESTADO *e, COORDENADA c);

/**
\brief Função booleana que verifica se a próxima jogada é válida
@param e Apontador para o estado
@param c A coordenada
 */
int jogada_valida(ESTADO *e, COORDENADA c);

/**
\brief Função que retorna o erro OK se a jogada é valida, se não retorna o respetivo erro.
@param e Apontador para Estado
@param c A Coordenada
*/
ERROS jogar(ESTADO *e, COORDENADA c);

/**
\brief Função que atribui uma prioridade as casas dependendo do jogador:
 * Para o jogador 1, a prioridade vai aumentando na diagonal, do canto superior direito para o canto inferior esquerdo;
 * Para o jogador 2, a prioridade vai aumentando na diagonal, mas no sentido oposto.
@param e Apontador para o estado
@param plr inteiro para número do jogador
@param c A Coordenada
*/
int prioridade_casa(ESTADO *e, int plr, COORDENADA c);

/**
\brief Função que recebe um ESTADO e uma LISTA de casas vizinhas vazias e devolve a COORDENADA da melhor jogada segundo a Euristica Euclidiana.
@param e Apontador para o estado
@param L A lista
@param plr inteiro para número do jogador
*/
COORDENADA jogadaEclidiana(ESTADO *e,LISTA l1, int plr);

/**
\brief Função que verifica se a peça branca está presa e se sim, devolve um, se não retorna zero.
@param e Apontador para o Estado
*/
int branca_presa(ESTADO *e);

/**
\brief Função que verifica se o jogo acabou e se sim então devolve o nº do jogador vencedor, caso contrário devolve zero
@param e Apontador para o Estado
*/
int end_game(ESTADO *e);


#endif //LI2PL7G05_LOGICA_DO_PROGRAMA_H
