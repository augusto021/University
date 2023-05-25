/**
@file Listas.h
Definição das estratégias da heurísticas.
*/

#ifndef LI2PL7G05_LISTAS_H
#define LI2PL7G05_LISTAS_H
#include "Dados.h"
#include <stdlib.h>

/**========================================MODULO DAS LISTAS LIGADAS==================================================*/

typedef struct sLista{
    void *variavel;
    struct sLista *prox;
} Nodo,  *LISTA;

/**
\brief Função que insere um valor na cabeça da lista.
*/
LISTA criar_lista();

/**
\brief Função que insere um valor na cabeça da lista.
@param L A lista
@param valor Apontador para uma variável genérica
*/
LISTA insere_cabeca(LISTA L, void *valor);

/**
\brief Função que devolve a cabeça da lista.
@param L A lista
 */
void *devolve_cabeca(LISTA L);

/**
\brief Função que devolve a cauda da lista.
@param L A lista
 */
LISTA proximo(LISTA L);

/**
\brief Função que remove a cabeça da lista (libertando o espaço ocupado) e devolve a cauda.
@param L A lista
 */
LISTA remove_cabeca(LISTA L);

/**
\brief Função que devolve verdadeiro se a lista é vazia.
@param L A lista
 */
int lista_esta_vazia(LISTA L);

/**
\brief Função que devolve verdadeiro se a lista é vazia.
@param L A lista
*/
int length_lista(LISTA L);

/**
\brief Função que cria a lista de casas vazia á volta da peça branca.
@param e Apontador para o estado
@param c A Coordenada
*/
LISTA armazena_branca(ESTADO *e,COORDENADA c);


#endif //LI2PL7G05_LISTAS_H
